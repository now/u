#include "rb_includes.h"

/* @return [U::String] The substring [0, min({#length}, 1)], inheriting any
 *   taint or untrust */
VALUE
rb_u_string_chr(VALUE self)
{
        return rb_u_string_substr(self, 0, 1);
}
