#include "rb_includes.h"

/* @return [U::String] The case-folding of the receiver, inheriting any taint
 *   and untrust */
VALUE
rb_u_string_foldcase(VALUE self)
{
        return _rb_u_string_convert(self, u_foldcase);
}
