#include "rb_includes.h"

/* Tests if this {U::String} only contains “cased” characters.  A cased
 * character is either in one of the categories
 *
 * * Letter, uppercase (Lu)
 * * Letter, lowercase (Ll)
 * * Letter, titlecase (Lt) categories
 *
 * or has the derived properties Other_Uppercase or Other_Lowercase.
 *
 * @return [Boolean] `True` if this {U::String} only contains “cased”
 *   characters. */
VALUE
rb_u_string_cased(VALUE self)
{
        return _rb_u_character_test(self, unichar_iscased);
}
