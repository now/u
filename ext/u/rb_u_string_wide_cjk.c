#include "rb_includes.h"

/* @overload wide_cjk?
 *
 *   Returns true if the receiver contains only “wide” and “ambiguously wide”
 *   characters.  Wide and ambiguously wide character are those that have their
 *   East_Asian_Width property set to Ambiguous, Wide or Fullwidth.
 *
 *   This is mostly useful for determining how many “cells” a character will
 *   take up on a terminal or similar cell-based display.
 *
 *   @return [Boolean]
 *   @see http://www.unicode.org/reports/tr11/
 *     Unicode Standard Annex #11: East Asian Width
 *   @see #wide?
 *   @see #width */
VALUE
rb_u_string_wide_cjk(VALUE self)
{
        return _rb_u_character_test(self, unichar_iswide_cjk);
}
