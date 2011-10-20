#include "rb_includes.h"

/* Reverses this {U::String}
 *
 * Reversing a string results in a string where all characters have been
 * reversed.  This doesn’t take into account proper handling of combining
 * marks, direction indicators, and similarly relevant characters, so this
 * method is mostly useful when you know the contents of the string is simple
 * and the result isn’t intended for display.
 *
 * @return [U::String] Reversed version of `self` */
VALUE
rb_u_string_reverse(VALUE self)
{
        const UString *string = RVAL2USTRING(self);
        long length = USTRING_LENGTH(string);

        char *reversed = u_reverse_n(USTRING_STR(string), length);

        return rb_u_string_new_own(reversed, length);
}
