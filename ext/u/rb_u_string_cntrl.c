#include "rb_includes.h"

/* Tests if this {U::String} only contains characters in the Other, control
 * (Cc) category, such as U+000A LINE FEED (LF) and U+001B ESCAPE.
 *
 * @return [Boolean] `True` if this {U::String} only contains characters in the
 *   Other, control (Cc) category */
VALUE
rb_u_string_cntrl(VALUE self)
{
        return _rb_u_character_test(self, unichar_iscntrl);
}
