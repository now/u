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
        return _rb_u_string_convert(self, u_mirror);
}
