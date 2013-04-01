#include "rb_includes.h"

/* Returns the width of the receiver.  The width is defined as the sum of the
 * number of “cells” on a terminal or similar cell-based display that the
 * characters in the string will require.
 *
 * Characters that are {#wide?} have a width of 2.  Characters that are
 * {#zero_width?} have a width of 0.  Other characters have a width of 1.
 *
 * @return [Integer]
 * @see http://www.unicode.org/reports/tr11/
 *   Unicode Standard Annex #11: East Asian Width
 * @see #wide?
 * @see #wide_cjk? */
VALUE
rb_u_string_width(VALUE self)
{
        const struct rb_u_string *string = RVAL2USTRING(self);

        return UINT2NUM(u_width_n(USTRING_STR(string), USTRING_LENGTH(string)));
}
