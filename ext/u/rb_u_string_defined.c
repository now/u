#include "rb_includes.h"

/* Tests if this {U::String} only contains characters not in the categories
 * Other, not assigned (Cn) or Other, surrogate (Cs), such as ‘A’, ‘1’, and
 * many more.
 *
 * @return [Boolean] `True` if this {U::String} only contains characters not in
 *   the categories Other, not assigned (Cn) or Other, surrogate (Cs). */
VALUE
rb_u_string_defined(VALUE self)
{
        return _rb_u_character_test(self, unichar_isdefined);
}
