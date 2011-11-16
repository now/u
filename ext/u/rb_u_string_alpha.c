#include "rb_includes.h"

/* Tests if this {U::String} only contains characters in the Letter Unicode
 * category.  That is, characters that belong to any of the categories
 *
 * * Letter, lowercase (Ll)
 * * Letter, uppercase (Lu)
 * * Letter, titlecase (Lt)
 * * Letter, modifier (Lm)
 * * Letter, other (Lo)
 *
 * such as ‘A’, ‘b’, and ‘ǅ’, will pass.
 *
 * @return [Boolean] `True` if this {U::String} only contains characters in the
 *   Alpha Unicode category. */
VALUE
rb_u_string_alpha(VALUE self)
{
        return _rb_u_character_test(self, unichar_isalpha);
}
