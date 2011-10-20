#include "rb_includes.h"

/* @overload include?(substring)
 *
 * Checks if _substring_ is a substring of `self`.
 *
 * Note that this check is done by byte comparison.
 *
 * @param [#to_str] substring Substring to check for
 * @return [Boolean] `True` if {#index}`(`_substring_`)` ≠ `nil` */
VALUE
rb_u_string_include(VALUE self, VALUE substring)
{
        return rb_u_string_index(self, substring, 0) != -1 ? Qtrue : Qfalse;
}
