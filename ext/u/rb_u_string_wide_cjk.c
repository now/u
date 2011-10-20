#include "rb_includes.h"

/* Tests if this {U::String} only contains characters with their East_Asian_Width
 * property set to Ambiguous, Wide, or Fullwidth.
 *
 * This is mostly useful on a terminal or similar cell-based display.
 *
 * See http://www.unicode.org/reports/tr11/ for more details.
 *
 * @return [Boolean] `True` if this {U::String} only contains characters with
 *   their East_Asian_Width property set to Ambiguous, Wide, or Fullwidth. */
VALUE
rb_u_string_wide_cjk(VALUE self)
{
        return _rb_u_character_test(self, unichar_iswide_cjk);
}
