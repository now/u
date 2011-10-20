#include "rb_includes.h"

/* Checks if this {U::String} has been case folded.
 *
 * The actual check is if _a_ = _a_{#foldcase}, where _a_ =
 * `self`{#normalize}`(:nfd)`.
 *
 * @return [Boolean] `True` if `self` has been case folded */
VALUE
rb_u_string_folded(VALUE self)
{
        return _rb_u_string_test(self, u_foldcase_n);
}
