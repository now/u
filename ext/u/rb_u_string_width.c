#include "rb_includes.h"

/* Determines the width of this {U::String}.
 *
 * Characters that are {#wide?} have a width of 2.  Characters that are
 * {#zero_width?} have a width of 0.  Other characters have a width of 1.
 *
 * This calculation is mostly useful on a terminal or similar cell-based
 * display.
 *
 * See http://www.unicode.org/reports/tr11/ for more details.
 *
 * @see #wide?
 *
 * @return [Integer] The sum of the widths of the characters of `self` */
VALUE
rb_u_string_width(VALUE self)
{
        const UString *string = RVAL2USTRING(self);

        return UINT2NUM(u_width_n(USTRING_STR(string), USTRING_LENGTH(string)));
}
