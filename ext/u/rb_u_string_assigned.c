#include "rb_includes.h"

/* Tests if this {U::String} only contains assigned characters.  Another way of
 * phrasing that is “only contains code points that have been assigned a code
 * value”.
 *
 * @return [Boolean] `True` if this {U::String} only contains assigned
 *   characters. */
VALUE
rb_u_string_assigned(VALUE self)
{
        return _rb_u_character_test(self, unichar_isassigned);
}
