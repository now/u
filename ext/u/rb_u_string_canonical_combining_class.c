#include "rb_includes.h"

/* Returns the canonical combining class of the characters of the receiver.
 *
 * The canonical combining class of a character is a number in the range [0,
 * 254].  The canonical combining class is used when generating a canonical
 * ordering of the characters in a string.
 *
 * The empty string has a canonical combining class of 0.
 *
 * @raise [ArgumentError] If the receiver contains two characters belonging to
 *   different combining classes
 * @raise [ArgumentError] If the receiver contains an incomplete UTF-8 sequence
 * @raise [ArgumentError] If the receiver contains an invalid UTF-8 sequence
 * @return [Fixnum] */
VALUE
rb_u_string_canonical_combining_class(VALUE self)
{
        const struct rb_u_string *string = RVAL2USTRING(self);
        const char *p = USTRING_STR(string);
        const char *end = USTRING_END(string);
        if (p == end)
                return 0;
        uint32_t c;
        p = u_decode(&c, p, end);
        int first = u_char_canonical_combining_class(c);
        while (p < end) {
                p = u_decode(&c, p, end);
                int value = u_char_canonical_combining_class(c);
                if (value != first)
                        rb_u_raise(rb_eArgError,
                                   "string consists of characters with different canonical combining class values: %d+, %d",
                                   first, value);
        }
        return INT2FIX(first);
}
