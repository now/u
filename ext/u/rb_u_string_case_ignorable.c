#include "rb_includes.h"

/* Tests if this {U::String} only contains “case ignorable” characters.  A case
 * ignorable character is defined as a character belonging to one of the
 * categories
 *
 * * Mark, nonspacing (Mn)
 * * Mark, enclosing (Me)
 * * Letter, modifier (Lm)
 * * Symbol, modifier (Sk)
 * * Other, format (Cf)
 *
 * or is one of the characters
 *
 * * U+0027 APOSTROPHE
 * * U+00AD SOFT HYPHEN
 * * U+2019 RIGHT SINGLE QUOTATION MARK
 *
 * See http://unicode.org/reports/tr21/tr21-5.html for more information.
 *
 * @return [Boolean] `True` if this {U::String} only contains “case ignorable”
 *   characters. */
VALUE
rb_u_string_case_ignorable(VALUE self)
{
        return _rb_u_character_test(self, unichar_iscaseignorable);
}
