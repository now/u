#include "rb_includes.h"

static char *
rb_u_string_justify_one_side(char *p, const struct rb_u_string *padding, long padding_width, long n)
{
        const char *padding_str = USTRING_STR(padding);
        long padding_size = USTRING_LENGTH(padding);

        long i = 0;

        for ( ; i + padding_width < n; i += padding_width, p += padding_size)
                memcpy(p, padding_str, padding_size);

        const char *q = padding_str;
        while (i < n) {
                // TODO Verify u_aref_char/u_next
                i += u_char_width(u_aref_char(q));
                q = u_next(q);
        }
        memcpy(p, padding_str, q - padding_str);
        p += q - padding_str;

        return p;
}

static long
rounding_size(const struct rb_u_string *padding, long padding_width, long n)
{
        const char *padding_str = USTRING_STR(padding);
        const char *q = padding_str, *end = padding_str + USTRING_LENGTH(padding);
        long r = n % padding_width;
        long i = 0;
        while (i < r && q < end) {
                // TODO Verify u_aref_char/u_next
		i += u_char_width(u_aref_char(q));
                q = u_next(q);
        }
        // NOTE I think i ≮ r is guaranteed, but I can’t seem to prove it, so
        // leave this in for safety.
        if (i < r)
                rb_u_raise(rb_eArgError,
                           "padding isn’t wide enough to complete rounding (%ld < %ld)",
                           i, r);
        if (i > r)
                rb_u_raise(rb_eArgError,
                           "padding is too wide to complete rounding (%ld > %ld)",
                           i, r);
        return q - padding_str;
}

static long
rb_u_string_justified_size(long string_size,
                           const struct rb_u_string *padding, long padding_width,
                           long left_n, long right_n)
{
        long size;

        long left_n_2 = rounding_size(padding, padding_width, left_n);
        long right_n_2 = rounding_size(padding, padding_width, right_n);
        if ((size = left_n / padding_width + right_n / padding_width) >= LONG_MAX / USTRING_LENGTH(padding) ||
            (size *= USTRING_LENGTH(padding)) >= LONG_MAX - left_n_2 - right_n_2 ||
            (size += left_n_2 + right_n_2) >= LONG_MAX - string_size)
                rb_u_raise(rb_eArgError, "argument too big");
        size += string_size;

        return size;
}

static VALUE
rb_u_string_justify_impl(VALUE self,
                         const struct rb_u_string *string, long string_width,
                         const struct rb_u_string *padding, long padding_width,
                         long width, char jflag)
{
        long n = width - string_width;
        long left_n = (jflag == 'l') ? 0 : ((jflag == 'r') ? n : n / 2);
        long right_n = n - left_n;

        long string_size = USTRING_LENGTH(string);
        long justified_size = rb_u_string_justified_size(string_size,
                                                         padding, padding_width,
                                                         left_n, right_n);
        char *justified = ALLOC_N(char, justified_size + 1);

        char *p = rb_u_string_justify_one_side(justified, padding, padding_width, left_n);
        memcpy(p, USTRING_STR(string), string_size);
        p += string_size;
        p = rb_u_string_justify_one_side(p, padding, padding_width, right_n);
        justified[justified_size] = '\0';

        return rb_u_string_new_c_own(self, justified, justified_size);
}

static VALUE
rb_u_string_justify(int argc, VALUE *argv, VALUE self, char jflag)
{
        const struct rb_u_string *string = RVAL2USTRING(self);

        VALUE rbwidth, rbpadding;
        const struct rb_u_string *padding = USTRING_LOCAL(Qnil, " ", 1);
        long padding_width = 1;
        if (rb_scan_args(argc, argv, "11", &rbwidth, &rbpadding) == 2) {
                padding = RVAL2USTRING_ANY(rbpadding);
                padding_width = u_width_n(USTRING_STR(padding), USTRING_LENGTH(padding));
                if (padding_width == 0)
                        rb_u_raise(rb_eArgError, "zero-width padding");
        }

        long string_width = u_width_n(USTRING_STR(string), USTRING_LENGTH(string));

        long width = NUM2LONG(rbwidth);
        if (width < 0 || string_width >= width)
                return self;

        VALUE result = rb_u_string_justify_impl(self,
                                                string, string_width,
                                                padding, padding_width,
                                                width, jflag);
        if (!NIL_P(rbpadding))
                OBJ_INFECT(result, rbpadding);
        return result;
}

/* @overload center(width, padding = ' ')
 *   @param [#to_int] width
 *   @param [U::String, #to_str] padding
 *   @raise [ArgumentError] If PADDING{#width} = 0
 *   @raise [ArgumentError] If characters inside PADDING that should be used
 *     for round-off padding are too wide
 *   @return [U::String] The receiver padded as evenly as possible on both
 *     sides with PADDING to make it max({#length}, WIDTH) wide, inheriting any
 *     taint and untrust from the receiver and also from PADDING if PADDING is
 *     used
 *   @see #ljust
 *   @see #rjust */
VALUE
rb_u_string_center(int argc, VALUE *argv, VALUE self)
{
        return rb_u_string_justify(argc, argv, self, 'c');
}

/* @overload ljust(width, padding = ' ')
 *   @param [#to_int] width
 *   @param [U::String, #to_str] padding
 *   @raise [ArgumentError] If PADDING{#width} = 0
 *   @raise [ArgumentError] If characters inside PADDING that should be used
 *     for round-off padding are too wide
 *   @return [U::String] The receiver padded on the right with PADDING to make
 *     it max({#length}, WIDTH) wide, inheriting any taint and untrust from
 *     the receiver and also from PADDING if PADDING is used
 *   @see #center
 *   @see #rjust */
VALUE
rb_u_string_ljust(int argc, VALUE *argv, VALUE self)
{
        return rb_u_string_justify(argc, argv, self, 'l');
}

/* @overload rjust(width, padding = ' ')
 *   @param [#to_int] width
 *   @param [U::String, #to_str] padding
 *   @raise [ArgumentError] If PADDING{#width} = 0
 *   @raise [ArgumentError] If characters inside PADDING that should be used
 *     for round-off padding are too wide
 *   @return [U::String] The receiver padded on the left with PADDING to make
 *     it max({#length}, WIDTH) wide, inheriting any taint and untrust from the
 *     receiver and also from PADDING if PADDING is used
 *   @see #center
 *   @see #ljust */
VALUE
rb_u_string_rjust(int argc, VALUE *argv, VALUE self)
{
        return rb_u_string_justify(argc, argv, self, 'r');
}
