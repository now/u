#include "rb_includes.h"

/* Tests if this {U::String} only contains characters in the Number, decimal
 * digit (Nd) category, such as ‘1’, ‘2’, and ‘3’.
 *
 * @return [Boolean] `True` if this {U::String} only contains characters in the
 *   Number, decimal digit (Nd) category. */
VALUE
rb_u_string_digit(VALUE self)
{
        return _rb_u_character_test(self, unichar_isdigit);
}
