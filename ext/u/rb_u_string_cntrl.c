#include "rb_includes.h"

/* @overload cntrl?
 *   @return [Boolean] True if the receiver contains only characters in the
 *     general category Other, control (Cc) */
VALUE
rb_u_string_cntrl(VALUE self)
{
        return _rb_u_character_test(self, unichar_iscntrl);
}
