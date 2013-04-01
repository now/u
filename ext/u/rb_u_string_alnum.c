#include "rb_includes.h"

/* @overload alnum?
 *   @return [Boolean] True if the receiver contains only characters in the
 *     general categories Letter and Number */
VALUE
rb_u_string_alnum(VALUE self)
{
        return _rb_u_character_test(self, u_char_isalnum);
}
