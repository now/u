#include "rb_includes.h"

/* @overload defined?
 *   @return [Boolean] True if the receiver contains only characters not in the
 *     general categories Other, not assigned (Cn) and Other, surrogate (Cs) */
VALUE
rb_u_string_defined(VALUE self)
{
        return _rb_u_character_test(self, unichar_isdefined);
}
