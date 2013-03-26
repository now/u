#include "rb_includes.h"

/* @overload valid?
 *   @return [Boolean] True if the receiver contains only valid Unicode
 *     characters */
VALUE
rb_u_string_valid(VALUE self)
{
        return _rb_u_character_test(self, unichar_isvalid);
}
