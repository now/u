#include "rb_includes.h"

/* Tests if this {U::String} only contains wide characters.  Wide character are
 * those that have their East_Asian_Width property set to Wide or Fullwidth.
 *
 * This is mostly useful on a terminal or similar cell-based display.
 *
 * See http://www.unicode.org/reports/tr11/ for more details.
 *
 * @see #width
 *
 * @return [Boolean] `True` if this {U::String} only contains wide
 *   characters */
VALUE
rb_u_string_wide(VALUE self)
{
        return _rb_u_character_test(self, unichar_iswide);
}
