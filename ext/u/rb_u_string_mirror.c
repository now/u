#include "rb_includes.h"

/* Returns the mirroring of the receiver, inheriting any taint and untrust.
 *
 * Mirroring is done by replacing characters in the string with their
 * horizontal mirror image, if any, in text that is laid out from right to
 * left.  For example, ‘(’ becomes ‘)’ and ‘)’ becomes ‘(’.
 *
 * @return [U::String]
 * @see http://www.unicode.org/reports/tr9/
 *   Unicode Standard Annex #9: Unicode Bidirectional Algorithm */
VALUE
rb_u_string_mirror(VALUE self)
{
        const struct rb_u_string *string = RVAL2USTRING(self);

        size_t n = u_mirror(NULL, 0, USTRING_STR(string), USTRING_LENGTH(string));
        char *mirrored = ALLOC_N(char, n + 1);
        u_mirror(mirrored, n + 1, USTRING_STR(string), USTRING_LENGTH(string));

        return rb_u_string_new_c_own(self, mirrored, n);
}
