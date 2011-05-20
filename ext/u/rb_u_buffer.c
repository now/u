#include <ruby.h>
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

        /* TODO: Don’t use + 1.  We don’t use \0. */
        long allocate = nearest_power(1, buffer->length + additional + 1);
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

static VALUE
rb_u_buffer_initialize(int argc, VALUE *argv, VALUE self)
{
        UBuffer *buffer = RVAL2UBUFFER(self);
        VALUE rbsize;

        rb_scan_args(argc, argv, "01", &rbsize);
        long size = NIL_P(rbsize) ? 127 : NUM2LONG(rbsize);

        u_buffer_maybe_expand(buffer, size);

        return Qnil;
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

/*
static VALUE
rb_u_buffer_initialize_copy(VALUE self, VALUE rboriginal)
{
        UString *string = RVAL2USTRING(self);
        const UString *original = RVAL2USTRING(rboriginal);

        if (string == original)
                return self;

        string->rb = original->rb;
        string->c = original->c;
        string->length = original->length;

        OBJ_INFECT(self, rboriginal);

        return self;
}
*/

void
Init_u_buffer(VALUE mU)
{
        rb_cUBuffer = rb_define_class_under(mU, "Buffer", rb_cData);

        rb_define_alloc_func(rb_cUBuffer, rb_u_buffer_alloc);
        rb_define_private_method(rb_cUBuffer, "initialize", rb_u_buffer_initialize, -1);
        /*
        rb_define_private_method(rb_cUBuffer, "initialize_copy", rb_u_buffer_initialize_copy, 1);
        */
        /*
        rb_define_method(rb_cUString, "%", rb_u_string_format_m, 1);
        rb_define_method(rb_cUString, "*", rb_u_string_times, 1);
        rb_define_method(rb_cUString, "+", rb_u_string_plus, 1);
        rb_define_method(rb_cUString, "<=>", rb_u_string_collate, 1);
        rb_define_method(rb_cUString, "==", rb_u_string_equal, 1);
        rb_define_method(rb_cUString, "===", rb_u_string_equal, 1);
        rb_define_method(rb_cUString, "=~", rb_u_string_match, 1);
        rb_define_method(rb_cUString, "eql?", rb_u_string_eql, 1);
        rb_define_method(rb_cUString, "bytes", rb_u_string_each_byte, 0);
        rb_define_method(rb_cUString, "casecmp", rb_u_string_casecmp, 1);
        rb_define_method(rb_cUString, "center", rb_u_string_center, -1);
        rb_define_method(rb_cUString, "chars", rb_u_string_each_char, 0);
        rb_define_method(rb_cUString, "[]", rb_u_string_aref_m, -1);
        rb_define_method(rb_cUString, "chomp", rb_u_string_chomp, -1);
        rb_define_method(rb_cUString, "chop", rb_u_string_chop, 0);
        rb_define_method(rb_cUString, "count", rb_u_string_count, -1);
        rb_define_method(rb_cUString, "delete", rb_u_string_delete, -1);
        rb_define_method(rb_cUString, "downcase", rb_u_string_downcase, 0);
        rb_define_method(rb_cUString, "each", rb_u_string_each_line, -1);
        rb_define_method(rb_cUString, "each_byte", rb_u_string_each_byte, 0);
        rb_define_method(rb_cUString, "each_char", rb_u_string_each_char, 0);
        rb_define_method(rb_cUString, "each_line", rb_u_string_each_line, -1);
        rb_define_method(rb_cUString, "empty?", rb_u_string_empty, 0);
        rb_define_method(rb_cUString, "end_with?", rb_u_string_ends_with, -1);
        rb_define_method(rb_cUString, "ends_with?", rb_u_string_ends_with, -1);
        rb_define_method(rb_cUString, "foldcase", rb_u_string_foldcase, 0);
        rb_define_method(rb_cUString, "format", rb_u_string_format_m, 1);
        rb_define_method(rb_cUString, "gsub", rb_u_string_gsub, -1);
        rb_define_method(rb_cUString, "hash", rb_u_string_hash, 0);
        rb_define_method(rb_cUString, "hex", rb_u_string_hex, 0);
        rb_define_method(rb_cUString, "include?", rb_u_string_include, 1);
        rb_define_method(rb_cUString, "index", rb_u_string_index_m, -1);
        rb_define_method(rb_cUString, "inspect", rb_u_string_inspect, 0);
        rb_define_method(rb_cUString, "intern", rb_u_string_to_sym, 0);
        rb_define_method(rb_cUString, "length", rb_u_string_length, 0);
        rb_define_method(rb_cUString, "lines", rb_u_string_each_line, -1);
        rb_define_method(rb_cUString, "ljust", rb_u_string_ljust, -1);
        rb_define_method(rb_cUString, "lstrip", rb_u_string_lstrip, 0);
        rb_define_method(rb_cUString, "normalize", rb_u_string_normalize, -1);
        rb_define_method(rb_cUString, "oct", rb_u_string_oct, 0);
        rb_define_method(rb_cUString, "reverse", rb_u_string_reverse, 0);
        rb_define_method(rb_cUString, "rindex", rb_u_string_rindex_m, -1);
        rb_define_method(rb_cUString, "rjust", rb_u_string_rjust, -1);
        rb_define_method(rb_cUString, "rstrip", rb_u_string_rstrip, 0);
        rb_define_method(rb_cUString, "squeeze", rb_u_string_squeeze, -1);
        rb_define_method(rb_cUString, "strip", rb_u_string_strip, 0);
        rb_define_method(rb_cUString, "to_i", rb_u_string_to_i, -1);
        rb_define_method(rb_cUString, "to_s", rb_u_string_to_str, 0);
        rb_define_method(rb_cUString, "to_str", rb_u_string_to_str, 0);
        rb_define_method(rb_cUString, "to_sym", rb_u_string_to_sym, 0);
        rb_define_method(rb_cUString, "tr", rb_u_string_tr, 2);
        rb_define_method(rb_cUString, "tr_s", rb_u_string_tr_s, 2);
        rb_define_method(rb_cUString, "upcase", rb_u_string_upcase, 0);
        */
        rb_define_method(rb_cUBuffer, "to_u", rb_u_buffer_to_u, 0);
        rb_define_method(rb_cUBuffer, "to_u!", rb_u_buffer_to_u_bang, 0);
}
