#include "rb_includes.h"

/* Returns the combining class of the characters of the receiver.
 *
 * The combining class of a character is a number in the range [0, 254].  The
 * combining class is used when generating a canonical ordering of the
 * characters in a string.
 *
 * @raise [ArgumentError] If the receiver contains two characters belonging to
 *   different combining classes
 * @raise [ArgumentError] If the receiver contains an incomplete UTF-8 sequence
 * @raise [ArgumentError] If the receiver contains an invalid UTF-8 sequence
 * @return [Fixnum] */
VALUE
rb_u_string_combining_class(VALUE self)
{
        int current = -1;

        const UString *string = RVAL2USTRING(self);

        const char *p = USTRING_STR(string);
        const char *end = USTRING_END(string);
        while (p < end) {
                int combining_class = u_char_combining_class(u_aref_char_validated_n(p, end - p));

                if (current == -1)
                        current = combining_class;
                else if (combining_class != current)
                        rb_u_raise(rb_eArgError,
                                   "string consists of more than one combining class: %d+, %d",
                                   current,
                                   combining_class);

                p = u_next(p);
        }

        return INT2FIX(current);
}
