#include "rb_includes.h"

/* Tests if this {U::String} only contains “printable” characters.  Printable
 * characters are those not in the Other Unicode category, that is, one of the
 * following categories:
 *
 * * Other, control (Cc)
 * * Other, format (Cf)
 * * Other, not assigned (Cn)
 * * Other, surrogate (Cs)
 *
 * A string that passes this test is generally considered to contain characters
 * that are “printable”.
 *
 * @return [Boolean] `True` if this {U::String} only contains characters not in
 *   the Other Unicode category. */
VALUE
rb_u_string_print(VALUE self)
{
        return _rb_u_character_test(self, unichar_isprint);
}
