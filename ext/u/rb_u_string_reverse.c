#include "rb_includes.h"

/* @return [U::String] The reversal of the receiver, inheriting any taint and
 *   untrust from the receiver
 * @note This doesn’t take into account proper handling of combining marks,
 *   direction indicators, and similarly relevant characters, so this method is
 *   mostly useful when you know the contents of the string is simple and the
 *   result isn’t intended for display. */
VALUE
rb_u_string_reverse(VALUE self)
{
        return _rb_u_string_convert(self, u_reverse);
}
