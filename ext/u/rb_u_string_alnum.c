#include "rb_includes.h"

/* Tests if this {U::String} only contains characters in the Letter or Number
 * Unicode categories, that is, characters that belong to any of the categories
 *
 * * Letter, lowercase (Ll)
 * * Letter, uppercase (Lu)
 * * Letter, titlecase (Lt)
 * * Letter, modifier (Lm)
 * * Letter, other (Lo)
 * * Number, decimal digit (Nd)
 * * Number, letter (Nl)
 * * Number, other (No)
 *
 * such as ‘A’, ‘1’, and ‘½’.
 *
 * @return [Boolean] `True` if this {U::String} only contains characters in the
 *   Letter or Number Unicode categories. */
VALUE
rb_u_string_alnum(VALUE self)
{
        return _rb_u_character_test(self, unichar_isalnum);
}
