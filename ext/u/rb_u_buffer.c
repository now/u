#include <ruby.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>
#include "u.h"
#include "private.h"
#include "rb_private.h"
#include "rb_u_buffer.h"
#include "rb_u_string.h"


#define RVAL2UBUFFER(object) \
        (Check_Type(object, T_DATA), (UBuffer *)DATA_PTR(object))

#define UBUFFER2RVAL(buffer) \
        Data_Wrap_Struct(rb_cUBuffer, NULL, rb_u_buffer_free, buffer)


/* TODO: Calling RVAL2UBUFFER costs about 0.02 seconds per 1000000 iterations,
 * so we don’t have to worry about that.  Still, do we provide a u_buffer /and/
 * a rb_u_buffer, or do we only have rb_u_buffer?  The thing that complicates
 * mathers is malloc/realloc.  I guess u_buffer could return NULL or false when
 * malloc/realloc fails and rb_u_buffer can check it.  I also guess that we can
 * extract u_buffer when it proves necessary.
 */
typedef struct _UBuffer UBuffer;

struct _UBuffer {
        char *c;
        long length;
        long allocated;
        long initially_allocated;
};


static VALUE rb_cUBuffer;


static void
rb_u_buffer_free(UBuffer *buffer)
{
        free(buffer->c);
        free(buffer);
}

static inline long
nearest_power(long base, long minimum)
{
        if (minimum < 0 || minimum * 2 < 0)
                return -1;

        long n = base;
        while (n < minimum)
                n *= 2;

        return n;
}

static void
u_buffer_maybe_expand(UBuffer *buffer, long additional)
{
        if (buffer->length + additional < buffer->allocated)
                return;

        long allocate = nearest_power(1, buffer->length + additional);
        if (allocate < 0)
                rb_raise(rb_eNoMemError,
                         "buffer would be too large: %ld + %ld + 1 > %ld",
                         buffer->length, additional, LONG_MAX);
        REALLOC_N(buffer->c, char, allocate);
        buffer->allocated = allocate;
}

static void
rb_u_buffer_reset(UBuffer *buffer)
{
        buffer->c = NULL;
        buffer->length = 0;
        buffer->allocated = 0;

        if (buffer->initially_allocated > 0)
                u_buffer_maybe_expand(buffer, buffer->initially_allocated);
}

static VALUE
rb_u_buffer_create(long size)
{
        UBuffer *buffer = ALLOC(UBuffer);

        buffer->initially_allocated = size;

        rb_u_buffer_reset(buffer);

        return UBUFFER2RVAL(buffer);
}

static VALUE
rb_u_buffer_alloc(UNUSED(VALUE klass))
{
        return rb_u_buffer_create(0);
}

VALUE
rb_u_buffer_new(void)
{
        return rb_u_buffer_create(0);
}

VALUE
rb_u_buffer_new_sized(long size)
{
        return rb_u_buffer_create(size);
}

VALUE
rb_u_buffer_append(VALUE self, const char *str, long length)
{
        UBuffer *buffer = RVAL2UBUFFER(self);

        u_buffer_maybe_expand(buffer, length);
        memcpy(buffer->c + buffer->length, str, length);
        buffer->length += length;

        return self;
}

VALUE
rb_u_buffer_append_unichar(VALUE self, unichar c)
{
        UBuffer *buffer = RVAL2UBUFFER(self);

        u_buffer_maybe_expand(buffer, MAX_UNICHAR_BYTE_LENGTH);
        buffer->length += unichar_to_u(c, buffer->c + buffer->length);

        return self;
}

VALUE
rb_u_buffer_append_unichar_n(VALUE self, unichar c, long n)
{
        if (n < 1)
                return self;

        UBuffer *buffer = RVAL2UBUFFER(self);

        if (c < 128) {
                u_buffer_maybe_expand(buffer, n);
                memset(buffer->c + buffer->length, c & 0x7f, n);
                buffer->length += n;
                return self;
        }

        char buf[MAX_UNICHAR_BYTE_LENGTH];
        int length = unichar_to_u(c, buf);
        u_buffer_maybe_expand(buffer, length * n);
        for (int i = 0; i < n; i++)
                memcpy(buffer->c + buffer->length + length * i, buf, length);
        buffer->length += length * n;

        return self;
}

#pragma GCC diagnostic ignored "-Wformat-nonliteral"
VALUE
rb_u_buffer_append_printf(VALUE self, size_t needed, const char *format, ...)
{
        UBuffer *buffer = RVAL2UBUFFER(self);

        u_buffer_maybe_expand(buffer, needed);

        va_list arguments;
        va_start(arguments, format);
        int length = vsnprintf(buffer->c + buffer->length, needed,
                               format, arguments);
        va_end(arguments);

        if (length < 0)
                rb_sys_fail("system vsnprintf(3) failed");

        if ((size_t)length >= needed)
                rb_raise(rb_eNotImpError,
                         "format string buffer calculation is wrong: %s (%zu < %zu)",
                         format, needed, (size_t)length);

        buffer->length += length;

        return self;
}
#pragma GCC diagnostic warning "-Wformat-nonliteral"

static VALUE
rb_u_buffer_initialize(int argc, VALUE *argv, VALUE self)
{
        UBuffer *buffer = RVAL2UBUFFER(self);
        VALUE rbsize;

        rb_scan_args(argc, argv, "01", &rbsize);
        long size = NIL_P(rbsize) ? 128 : NUM2LONG(rbsize);

        u_buffer_maybe_expand(buffer, size);

        return Qnil;
}

static VALUE
rb_u_buffer_initialize_copy(VALUE self, VALUE rboriginal)
{
        UBuffer *buffer = RVAL2UBUFFER(self);
        const UBuffer *original = RVAL2UBUFFER(rboriginal);

        /* TODO: Can this happen? */
        if (buffer == original)
                return self;

        buffer->initially_allocated = original->initially_allocated;

        rb_u_buffer_append(self, original->c, original->length);

        OBJ_INFECT(self, rboriginal);

        return self;
}

VALUE
rb_u_buffer_append_m(int argc, VALUE *argv, VALUE self)
{
        need_at_least_n_arguments(argc, 1);

        for (int i = 0; i < argc; i++)
                if (rb_obj_is_kind_of(argv[i], rb_cUBuffer)) {
                        const UBuffer *buffer = RVAL2UBUFFER(argv[i]);

                        rb_u_buffer_append(self, buffer->c, buffer->length);
                } else if (FIXNUM_P(argv[i]) || TYPE(argv[i]) == T_BIGNUM) {
                        unichar c = NUM2UINT(argv[i]);

/* TODO: This depends on an experimental API.  Modify this once the API is
 * stable. */
#if 0
                        if (rb_num_to_uint(argv[i], &c) != 0) {
                                if (FIXNUM_P(argv[i]))
                                        rb_raise(rb_eRangeError,
                                                 "%ld out of char range",
                                                 FIX2LONG(argv[i]));
                                else
                                        rb_raise(rb_eRangeError,
                                                 "Bignum out of char range");
                        }
#endif

                        if (!unichar_isvalid(c))
                                rb_raise(rb_eRangeError,
                                         "invalid Unicode character: %u",
                                         c);

                        rb_u_buffer_append_unichar(self, c);
                } else {
                        const UString *string = RVAL2USTRING_ANY(argv[i]);

                        rb_u_buffer_append(self,
                                           USTRING_STR(string),
                                           USTRING_LENGTH(string));
                }
        
        return self;
}

VALUE
rb_u_buffer_eql(VALUE self, VALUE rbother)
{
        if (self == rbother)
                return Qtrue;

        if (!rb_obj_is_kind_of(rbother, rb_cUBuffer))
                return Qfalse;

        const UBuffer *buffer = RVAL2UBUFFER(self);
        const UBuffer *other = RVAL2UBUFFER(rbother);

        return buffer->length == other->length &&
                memcmp(buffer->c, other->c, other->length) == 0 ?
                Qtrue : Qfalse;
}

VALUE
rb_u_buffer_hash(VALUE self)
{
        const UBuffer *buffer = RVAL2UBUFFER(self);

        return INT2FIX(rb_memhash(buffer->c, buffer->length));
}

VALUE
rb_u_buffer_to_s(VALUE self)
{
        const UBuffer *buffer = RVAL2UBUFFER(self);

        return rb_str_new(buffer->c, buffer->length);
}

VALUE
rb_u_buffer_to_u(VALUE self)
{
        const UBuffer *buffer = RVAL2UBUFFER(self);

        return rb_u_string_new(buffer->c, buffer->length);
}

VALUE
rb_u_buffer_to_u_bang(VALUE self)
{
        UBuffer *buffer = RVAL2UBUFFER(self);

        /* TODO: Really need to lock buffer here. */
        char *c = buffer->c;
        long length = buffer->length;
        rb_u_buffer_reset(buffer);

        REALLOC_N(c, char, length + 1);
        c[length] = '\0';

        return rb_u_string_new_own(c, length);
}

void
Init_u_buffer(VALUE mU)
{
        rb_cUBuffer = rb_define_class_under(mU, "Buffer", rb_cData);

        rb_define_alloc_func(rb_cUBuffer, rb_u_buffer_alloc);
        rb_define_private_method(rb_cUBuffer, "initialize", rb_u_buffer_initialize, -1);
        rb_define_private_method(rb_cUBuffer, "initialize_copy", rb_u_buffer_initialize_copy, 1);
        rb_define_method(rb_cUBuffer, "<<", rb_u_buffer_append_m, -1);
        rb_define_method(rb_cUBuffer, "==", rb_u_buffer_eql, 1);
        rb_define_method(rb_cUBuffer, "append", rb_u_buffer_append_m, -1);
        rb_define_method(rb_cUBuffer, "append_format", rb_u_buffer_append_format_m, -1);
        rb_define_method(rb_cUBuffer, "eql?", rb_u_buffer_eql, 1);
        rb_define_method(rb_cUBuffer, "hash", rb_u_buffer_hash, 0);
        rb_define_method(rb_cUBuffer, "to_s", rb_u_buffer_to_s, 0);
        rb_define_method(rb_cUBuffer, "to_u", rb_u_buffer_to_u, 0);
        rb_define_method(rb_cUBuffer, "to_u!", rb_u_buffer_to_u_bang, 0);
}
