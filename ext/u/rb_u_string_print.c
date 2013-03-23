#include "rb_includes.h"

/* @overload print?
 *   @return [Boolean] True if the receiver contains only characters not in the
 *     general category Other */
VALUE
rb_u_string_print(VALUE self)
{
        return _rb_u_character_test(self, unichar_isprint);
}
