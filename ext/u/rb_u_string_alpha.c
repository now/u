#include "rb_includes.h"

/* @overload alpha?
 *   @return [Boolean] True if the receiver contains only characters in the
 *     general category Alpha */
VALUE
rb_u_string_alpha(VALUE self)
{
        return _rb_u_character_test(self, unichar_isalpha);
}
