#include "rb_includes.h"

/* @overload include?(substring)
 *   @param [#to_str] substring
 *   @return [Boolean] True if {#index}(SUBSTRING) ≠ nil */
VALUE
rb_u_string_include(VALUE self, VALUE substring)
{
        return rb_u_string_index(self, substring, 0) != -1 ? Qtrue : Qfalse;
}
