#include "rb_includes.h"

/* Tests if this {U::String} only contains defined characters.  Defined
 * characters are characters not in the categories
 *
 * * Other, not assigned (Cn)
 * * Other, surrogate (Cs)
 *
 * such as ‘A’, ‘1’, and many more.
 *
 * @return [Boolean] `True` if this {U::String} only contains defined characters */
VALUE
rb_u_string_defined(VALUE self)
{
        return _rb_u_character_test(self, unichar_isdefined);
}
