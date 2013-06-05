/* -*- coding: utf-8 -*- */

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


#define RVAL2RBUBUFFER(object) \
        (Check_Type(object, T_DATA), (struct rb_u_buffer *)DATA_PTR(object))

#define UBUFFER2RVAL(buffer) \
        Data_Wrap_Struct(rb_cUBuffer, NULL, rb_u_buffer_free, buffer)


struct rb_u_buffer {
        char *c;
        long length;
        long allocated;
        long initially_allocated;
};


static VALUE rb_cUBuffer;


static void
rb_u_buffer_free(struct rb_u_buffer *buffer)
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
u_buffer_maybe_expand(struct rb_u_buffer *buffer, long additional)
{
        if (buffer->length + additional < buffer->allocated)
                return;

        long allocate = nearest_power(1, buffer->length + additional);
        if (allocate < 0)
                rb_u_raise(rb_eNoMemError,
                           "buffer would be too large: %ld + %ld + 1 > %ld",
                           buffer->length, additional, LONG_MAX);
        REALLOC_N(buffer->c, char, allocate);
        buffer->allocated = allocate;
}

static void
rb_u_buffer_reset(struct rb_u_buffer *buffer)
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
        struct rb_u_buffer *buffer = ALLOC(struct rb_u_buffer);

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
        struct rb_u_buffer *buffer = RVAL2RBUBUFFER(self);

        u_buffer_maybe_expand(buffer, length);
        memcpy(buffer->c + buffer->length, str, length);
        buffer->length += length;

        return self;
}

VALUE
rb_u_buffer_append_char(VALUE self, uint32_t c)
{
        struct rb_u_buffer *buffer = RVAL2RBUBUFFER(self);

        u_buffer_maybe_expand(buffer, U_CHAR_MAX_BYTE_LENGTH);
        buffer->length += u_char_to_u(c, buffer->c + buffer->length);

        return self;
}

VALUE
rb_u_buffer_append_char_n(VALUE self, uint32_t c, long n)
{
        if (n < 1)
                return self;

        struct rb_u_buffer *buffer = RVAL2RBUBUFFER(self);

        if (c < 128) {
                u_buffer_maybe_expand(buffer, n);
                memset(buffer->c + buffer->length, c & 0x7f, n);
                buffer->length += n;
                return self;
        }

        char buf[U_CHAR_MAX_BYTE_LENGTH];
        int length = u_char_to_u(c, buf);
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
        struct rb_u_buffer *buffer = RVAL2RBUBUFFER(self);

        u_buffer_maybe_expand(buffer, needed);

        va_list arguments;
        va_start(arguments, format);
        int length = vsnprintf(buffer->c + buffer->length, needed,
                               format, arguments);
        va_end(arguments);

        if (length < 0)
                rb_sys_fail("system vsnprintf(3) failed");

        if ((size_t)length >= needed)
                rb_u_raise(rb_eNotImpError,
                           "format string buffer calculation is wrong: %s (%"PRIuSIZE" < %"PRIuSIZE")",
                           format, needed, (size_t)length);

        buffer->length += length;

        return self;
}
#pragma GCC diagnostic warning "-Wformat-nonliteral"

/* @!visibility public
 * @overload new(size = 128)
 *
 *   Sets up a new buffer of SIZE bytes.
 *
 *   @param [#to_int] size */
static VALUE
rb_u_buffer_initialize(int argc, VALUE *argv, VALUE self)
{
        struct rb_u_buffer *buffer = RVAL2RBUBUFFER(self);
        VALUE rbsize;

        rb_scan_args(argc, argv, "01", &rbsize);
        long size = NIL_P(rbsize) ? 128 : NUM2LONG(rbsize);

        u_buffer_maybe_expand(buffer, size);

        return Qnil;
}

static VALUE
rb_u_buffer_initialize_copy(VALUE self, VALUE rboriginal)
{
        struct rb_u_buffer *buffer = RVAL2RBUBUFFER(self);
        const struct rb_u_buffer *original = RVAL2RBUBUFFER(rboriginal);

        if (buffer == original)
                return self;

        buffer->initially_allocated = original->initially_allocated;

        rb_u_buffer_append(self, original->c, original->length);

        OBJ_INFECT(self, rboriginal);

        return self;
}

/* @overload <<(*parts)
 *
 *   Append each _p_ in PARTS, append _q_ to the receiver, where _q_ =
 *   _p_#to_s, if _p_ is a U::Buffer, _q_ = _p_#chr, if _p_ is a Fixnum or
 *   Bignum, _q_ = _p_#to_str, if _p_ is a U::String or responds to #to_str.
 *
 *   @param [U::Buffer, Fixnum, Bignum, U::String, #to_str] parts
 *   @raise [RangeError] If a _p_ is a Fixnum or Bignum and ¬_p_#chr#valid?
 *   @return [self] */
VALUE
rb_u_buffer_append_m(int argc, VALUE *argv, VALUE self)
{
        need_at_least_n_arguments(argc, 1);

        for (int i = 0; i < argc; i++)
                if (RTEST(rb_obj_is_kind_of(argv[i], rb_cUBuffer))) {
                        const struct rb_u_buffer *buffer = RVAL2RBUBUFFER(argv[i]);

                        rb_u_buffer_append(self, buffer->c, buffer->length);
                        OBJ_INFECT(self, argv[i]);
                } else if (FIXNUM_P(argv[i]) || TYPE(argv[i]) == T_BIGNUM) {
                        uint32_t c = NUM2UINT(argv[i]);

/* TODO: This depends on an experimental API.  Modify this once the API is
 * stable. */
#if 0
                        if (rb_num_to_uint(argv[i], &c) != 0) {
                                if (FIXNUM_P(argv[i]))
                                        rb_u_raise(rb_eRangeError,
                                                   "%ld out of char range",
                                                   FIX2LONG(argv[i]));
                                else
                                        rb_u_raise(rb_eRangeError,
                                                   "Bignum out of char range");
                        }
#endif

                        if (!u_char_isvalid(c))
                                rb_u_raise(rb_eRangeError,
                                           "invalid Unicode character: %u",
                                           c);

                        rb_u_buffer_append_char(self, c);
                } else {
                        const struct rb_u_string *string = RVAL2USTRING_ANY(argv[i]);

                        rb_u_buffer_append(self,
                                           USTRING_STR(string),
                                           USTRING_LENGTH(string));
                        OBJ_INFECT(self, argv[i]);
                }

        return self;
}

/* @return [U::String] A UTF-8-encoded string of the receiver’s content */
VALUE
rb_u_buffer_to_u(VALUE self)
{
        const struct rb_u_buffer *buffer = RVAL2RBUBUFFER(self);

        return rb_u_string_new_c(self, buffer->c, buffer->length);
}

/* @return [U::String] The UTF-8-encoded string of the receiver’s content after
 *   clearing it from the receiver
 * @note This method differs from {#to_u} in that it doesn’t copy the result,
 *   so it’s generally faster; call it when you’re done building your
 *   {U::String}. */
VALUE
rb_u_buffer_to_u_bang(VALUE self)
{
        struct rb_u_buffer *buffer = RVAL2RBUBUFFER(self);

        char *c = buffer->c;
        long length = buffer->length;
        rb_u_buffer_reset(buffer);

        REALLOC_N(c, char, length + 1);
        c[length] = '\0';

        return rb_u_string_new_c_own(self, c, length);
}

/* @return [String] A UTF-8-encoded string of the receiver’s content */
VALUE
rb_u_buffer_to_s(VALUE self)
{
        const struct rb_u_buffer *buffer = RVAL2RBUBUFFER(self);

        VALUE result = rb_u_str_new(buffer->c, buffer->length);
        OBJ_INFECT(result, self);
        return result;
}

/* @return [Integer] The number of characters in the receiver */
VALUE
rb_u_buffer_length(VALUE self)
{
        const struct rb_u_buffer *buffer = RVAL2RBUBUFFER(self);
        return UINT2NUM(u_n_chars_n(buffer->c, buffer->length));
}

/* @return [Integer] The number of bytes required to represent the receiver */
VALUE
rb_u_buffer_bytesize(VALUE self)
{
        const struct rb_u_buffer *buffer = RVAL2RBUBUFFER(self);
        return UINT2NUM(buffer->length);
}

/* Returns the width of the receiver.  The width is defined as the sum of the
 * number of “cells” on a terminal or similar cell-based display that the
 * characters in the string will require.
 *
 * Characters that are {U::String#wide?} have a width of 2.  Characters that
 * are {U::String#zero_width?} have a width of 0.  Other characters have a
 * width of 1.
 *
 * @return [Integer]
 * @see http://www.unicode.org/reports/tr11/
 *   Unicode Standard Annex #11: East Asian Width */
VALUE
rb_u_buffer_width(VALUE self)
{
        const struct rb_u_buffer *buffer = RVAL2RBUBUFFER(self);
        return UINT2NUM(u_width_n(buffer->c, buffer->length));
}

/* @overload ==(other)
 *   @param [U::Buffer] other
 *   @return [Boolean] True if the receiver’s class and content equal those of
 *     OTHER */
VALUE
rb_u_buffer_eql(VALUE self, VALUE rbother)
{
        if (self == rbother)
                return Qtrue;

        if (!RTEST(rb_obj_is_kind_of(rbother, rb_cUBuffer)))
                return Qfalse;

        const struct rb_u_buffer *buffer = RVAL2RBUBUFFER(self);
        const struct rb_u_buffer *other = RVAL2RBUBUFFER(rbother);

        return buffer->length == other->length &&
                memcmp(buffer->c, other->c, other->length) == 0 ?
                Qtrue : Qfalse;
}

/* @return [Fixnum] The hash value of the receiver’s content */
VALUE
rb_u_buffer_hash(VALUE self)
{
        const struct rb_u_buffer *buffer = RVAL2RBUBUFFER(self);

        return INT2FIX(rb_memhash(buffer->c, buffer->length));
}

/* Document-class: U::Buffer
 *
 * A buffer for building {U::String}s.  Buffers should be used when you want to
 * create U::Strings step-wise, for example, when joining them together, or
 * reading some input.  Create a new buffer with {#initialize}, optionally
 * specifying an initial size.  Then, {#append} (or {#<<}) content to it.  You
 * can also {#append_format}ted content.  You can check the {#length}
 * ({#size}), {#bytesize}, and {#width} of the buffer, which can be useful if
 * you want to limit how much content you want to generate.  Once all content
 * has been appended, a buffer can be converted to a U::String via {#to_u} or
 * {#to_u!} depending on whether you want to let the buffer keep its content or
 * not.  You can also convert it to a String with {#to_s}.
 *
 * @example Benchmarking U::String#+ Versus U::Buffer#append/U::Buffer#to_u!
 *   require 'benchmark'
 *   require 'u-1.0'
 *   Benchmark.bm do |x|
 *     x.report do
 *       a = ''.u
 *       100000.times do
 *         a = a + 'a'
 *       end
 *     end
 *     x.report do
 *      b = U::Buffer.new
 *       100000.times do
 *         b.append 'a'
 *       end
 *       a = b.to_u!
 *     end
 *   end
 *   # ⇒
 *   #       user     system      total        real
 *   #   3.560000   0.650000   4.210000 (  4.726064)
 *   #   0.060000   0.000000   0.060000 (  0.057134) */
void
Init_u_buffer(VALUE mU)
{
        rb_cUBuffer = rb_define_class_under(mU, "Buffer", rb_cData);

        rb_define_alloc_func(rb_cUBuffer, rb_u_buffer_alloc);
        rb_define_private_method(rb_cUBuffer, "initialize", rb_u_buffer_initialize, -1);
        rb_define_private_method(rb_cUBuffer, "initialize_copy", rb_u_buffer_initialize_copy, 1);

        rb_define_method(rb_cUBuffer, "append", rb_u_buffer_append_m, -1);
        rb_define_alias(rb_cUBuffer, "<<", "append");
        rb_define_method(rb_cUBuffer, "append_format", rb_u_buffer_append_format_m, -1); /* in ext/u/rb_u_string_format.c */

        rb_define_method(rb_cUBuffer, "to_u", rb_u_buffer_to_u, 0);
        rb_define_method(rb_cUBuffer, "to_u!", rb_u_buffer_to_u_bang, 0);
        rb_define_method(rb_cUBuffer, "to_s", rb_u_buffer_to_s, 0);

        rb_define_method(rb_cUBuffer, "length", rb_u_buffer_length, 0);
        rb_define_alias(rb_cUBuffer, "size", "length");
        rb_define_method(rb_cUBuffer, "bytesize", rb_u_buffer_bytesize, 0);
        rb_define_method(rb_cUBuffer, "width", rb_u_buffer_width, 0);

        rb_define_method(rb_cUBuffer, "==", rb_u_buffer_eql, 1);
        rb_define_alias(rb_cUBuffer, "eql?", "==");
        rb_define_method(rb_cUBuffer, "hash", rb_u_buffer_hash, 0);
}
