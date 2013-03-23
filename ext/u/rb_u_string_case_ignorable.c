#include "rb_includes.h"

/* @overload case_ignorable?
 *
 *   @return [Boolean] True if the receiver contains only “case ignorable”
 *     characters, that is, characters in the general categories
 *
 *     * Other, format (Cf)
 *     * Letter, modifier (Lm)
 *     * Mark, enclosing (Me)
 *     * Mark, nonspacing (Mn)
 *     * Symbol, modifier (Sk)
 *
 *     and the characters
 *
 *     * U+0027 APOSTROPHE
 *     * U+00AD SOFT HYPHEN
 *     * U+2019 RIGHT SINGLE QUOTATION MARK
 *   @see http://unicode.org/reports/tr21/tr21-5.html
 *     Unicode Standard Annex #21: Case Mappings */
VALUE
rb_u_string_case_ignorable(VALUE self)
{
        return _rb_u_character_test(self, unichar_iscaseignorable);
}
