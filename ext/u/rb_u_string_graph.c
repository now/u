#include "rb_includes.h"

/* Tests if this {U::String} only contains characters not in the Other Unicode
 * category or the Space, separator (Zs) category, that is, one of the
 * following categories:
 *
 * * Other, control (Cc)
 * * Other, format (Cf)
 * * Other, not assigned (Cn)
 * * Other, surrogate (Cs)
 * * Space, separator (Zs)
 *
 * A string that passes this test is generally considered to contain characters
 * that are “printable” and don’t contain any space characters.
 *
 * @return [Boolean] `True` if this {U::String} only contains characters not in
 *   the Other Unicode category or the Space, separator (Zs) category. */
VALUE
rb_u_string_graph(VALUE self)
{
        return _rb_u_character_test(self, unichar_isgraph);
}
