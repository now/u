#include "rb_includes.h"

/* Extracts the substring [0, min({#length}, 1)].
 *
 * Any taint or untrust is inherited by the substring.
 *
 * @return [U::String] The extracted substring */
VALUE
rb_u_string_chr(VALUE self)
{
        return rb_u_string_substr(self, 0, 1);
}
