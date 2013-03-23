#include "rb_includes.h"

/* @overload digit?
 *   @return [Boolean] True if the receiver contains only characters in the
 *     general category Number, decimal digit (Nd) */
VALUE
rb_u_string_digit(VALUE self)
{
        return _rb_u_character_test(self, unichar_isdigit);
}
