#include "rb_includes.h"

/* Returns the canonical combining class of the characters of the receiver.
 *
 * The canonical combining class of a character is a number in the range [0,
 * 254].  The canonical combining class is used when generating a canonical
 * ordering of the characters in a string.
 *
 * @raise [ArgumentError] If the receiver contains two characters belonging to
 *   different combining classes
 * @raise [ArgumentError] If the receiver contains an incomplete UTF-8 sequence
 * @raise [ArgumentError] If the receiver contains an invalid UTF-8 sequence
 * @return [Fixnum] */
VALUE
rb_u_string_canonical_combining_class(VALUE self)
{
        int current = -1;

        const struct rb_u_string *string = RVAL2USTRING(self);

        const char *p = USTRING_STR(string);
        const char *end = USTRING_END(string);
        while (p < end) {
                int ccc = u_char_canonical_combining_class(u_dref_validated_n(p, end - p));

                if (current == -1)
                        current = ccc;
                else if (ccc != current)
                        rb_u_raise(rb_eArgError,
                                   "string consists of characters with different canonical combining class values: %d+, %d",
                                   current,
                                   ccc);

                p = u_next(p);
        }

        return INT2FIX(current);
}
