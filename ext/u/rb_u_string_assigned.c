#include "rb_includes.h"

/* @overload assigned?
 *   @return [Boolean] True if the receiver contains only code points that have
 *     been assigned a code value */
VALUE
rb_u_string_assigned(VALUE self)
{
        return _rb_u_character_test(self, unichar_isassigned);
}
