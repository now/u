#include "rb_includes.h"

/* Tests if this {U::String} only contains soft-dotted characters.  Soft-dotted
 * characters have the soft-dotted property and lose their dot if an accent is
 * applied to them, for example, ‘i’ and ‘j’.
 *
 * See http://unicode.org/review/pr-11.html for more information.
 *
 * @return [Boolean] `True` if this {U::String} only contains soft-dotted
 *   characters */
VALUE
rb_u_string_soft_dotted(VALUE self)
{
        return _rb_u_character_test(self, unichar_issoftdotted);
}
