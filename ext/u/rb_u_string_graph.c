#include "rb_includes.h"

/* @overload graph?
 *
 *   Returns true if the receiver contains only non-space “printable” characters.
 *
 *   Non-space “printable” character are those not in the general categories
 *   Other or Space, separator (Zs):
 *
 *   * Other, control (Cc)
 *   * Other, format (Cf)
 *   * Other, not assigned (Cn)
 *   * Other, surrogate (Cs)
 *   * Space, separator (Zs)
 *
 *   @return [Boolean] */
VALUE
rb_u_string_graph(VALUE self)
{
        return _rb_u_character_test(self, unichar_isgraph);
}
