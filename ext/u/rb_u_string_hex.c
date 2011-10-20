#include "rb_includes.h"
#include "rb_u_string_to_inum.h"

/* Alias for {#to_i}(16).
 *
 * @return [Integer] Result of {#to_i}(16) */
VALUE
rb_u_string_hex(VALUE self)
{
        return rb_u_string_to_inum(self, 16, false);
}
