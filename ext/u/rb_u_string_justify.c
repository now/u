#include "rb_includes.h"

static char *
rb_u_string_justify_one_side(char *p, const UString *padding, long padding_length, long n)
{
        const char *padding_str = USTRING_STR(padding);
        long padding_size = USTRING_LENGTH(padding);

        long i = 0;

        for ( ; i + padding_length < n; i += padding_length, p += padding_size)
                memcpy(p, padding_str, padding_size);

        const char *q = padding_str;
        while (i < n) {
                q = u_next(q);
                i++;
        }
        memcpy(p, padding_str, q - padding_str);
        p += q - padding_str;

        return p;
}

static long
rb_u_string_justified_size(long string_size,
                           const UString *padding, long padding_length,
                           long left_n, long right_n)
{
        long size;

        const char *padding_begin = USTRING_STR(padding);
        long left_n_2 = u_offset_to_pointer(padding_begin, left_n % padding_length) - padding_begin;
        long right_n_2 = u_offset_to_pointer(padding_begin, right_n % padding_length) - padding_begin;
        if ((size = left_n / padding_length + right_n / padding_length) >= LONG_MAX / USTRING_LENGTH(padding) ||
            (size *= USTRING_LENGTH(padding)) >= LONG_MAX - left_n_2 - right_n_2 ||
            (size += left_n_2 + right_n_2) >= LONG_MAX - string_size)
                rb_raise(rb_eArgError, "argument too big");
        size += string_size;

        return size;
}

static VALUE
rb_u_string_justify_impl(const UString *string, long string_length,
                         const UString *padding, long padding_length,
                         long width, char jflag)
{
        long n = width - string_length;
        long left_n = (jflag == 'l') ? 0 : ((jflag == 'r') ? n : n / 2);
        long right_n = n - left_n;

        long string_size = USTRING_LENGTH(string);
        long justified_size = rb_u_string_justified_size(string_size,
                                                         padding, padding_length,
                                                         left_n, right_n);
        char *justified = ALLOC_N(char, justified_size + 1);

        char *p = rb_u_string_justify_one_side(justified, padding, padding_length, left_n);
        memcpy(p, USTRING_STR(string), string_size);
        p += string_size;
        p = rb_u_string_justify_one_side(p, padding, padding_length, right_n);
        justified[justified_size] = '\0';

        return rb_u_string_new_own(justified, justified_size);
}

static VALUE
rb_u_string_justify(int argc, VALUE *argv, VALUE self, char jflag)
{
        const UString *string = RVAL2USTRING(self);

        VALUE rbwidth, rbpadding;
        const UString *padding = USTRING_LOCAL(Qnil, " ", 1);
        long padding_length = 1;
        if (rb_scan_args(argc, argv, "11", &rbwidth, &rbpadding) == 2) {
                padding = RVAL2USTRING_ANY(rbpadding);
                padding_length = u_length_n(USTRING_STR(padding), USTRING_LENGTH(padding));
                if (padding_length == 0)
                        rb_raise(rb_eArgError, "zero width padding");
        }

        long string_length = u_length_n(USTRING_STR(string), USTRING_LENGTH(string));

        long width = NUM2LONG(rbwidth);
        if (width < 0 || string_length >= width)
                return self;

        VALUE result = rb_u_string_justify_impl(string, string_length,
                                                padding, padding_length,
                                                width, jflag);
        OBJ_INFECT(result, self);
        if (!NIL_P(rbpadding))
                OBJ_INFECT(result, rbpadding);

        return result;
}

/* @overload center(width, padding = ' ')
 *
 *   Pads `self` as evenly as possible on both sides with _padding_ to make it
 *   max({#length}, _width_) wide.
 *
 *   @param [Integer] width Width of the resulting string
 *   @param [U::String, #to_str] padding String to pad the result with
 *   @raise [ArgumentError] If _padding_{#length} = 0
 *   @return [U::String] `self` padded as evenly as possible on both sides with
 *     _padding_
 *
 *   @see #ljust
 *   @see #rjust */
VALUE
rb_u_string_center(int argc, VALUE *argv, VALUE self)
{
        return rb_u_string_justify(argc, argv, self, 'c');
}

/* @overload ljust(width, padding = ' ')
 *
 *   Pads `self` on the right with _padding_ to make it max({#length}, _width_)
 *   wide.
 *
 *   @param [Integer] width Width of the resulting string
 *   @param [U::String, #to_str] padding String to pad the result with
 *   @raise [ArgumentError] If _padding_{#length} = 0
 *   @return [U::String] `self` padded on the right with _padding_
 *
 *   @see #center
 *   @see #rjust */
VALUE
rb_u_string_ljust(int argc, VALUE *argv, VALUE self)
{
        return rb_u_string_justify(argc, argv, self, 'l');
}

/* @overload rjust(width, padding = ' ')
 *
 *   Pads `self` on the left with _padding_ to make it max({#length}, _width_)
 *   wide.
 *
 *   @param [Integer] width Width of the resulting string
 *   @param [U::String, #to_str] padding String to pad the result with
 *   @raise [ArgumentError] If _padding_{#length} = 0
 *   @return [U::String] `self` padded on the left with _padding_
 *
 *   @see #center
 *   @see #ljust */
VALUE
rb_u_string_rjust(int argc, VALUE *argv, VALUE self)
{
        return rb_u_string_justify(argc, argv, self, 'r');
}
