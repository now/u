#include "rb_includes.h"

/* @overload title?
 *   @return [Boolean] True if the receiver contains only characters in the
 *     general category Letter, Titlecase (Lt) */
VALUE
rb_u_string_title(VALUE self)
{
        return _rb_u_character_test(self, u_char_istitle);
}
