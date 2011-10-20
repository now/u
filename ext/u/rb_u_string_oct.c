#include "rb_includes.h"
#include "rb_u_string_to_inum.h"

/* Alias for {#to_i}(8), but with the added provision that any leading base
 * specification will override the suggested octal (8) base, that is,
 * `'0b11'.u`{#oct} = 3, not 9.
 *
 * @return [Integer] Result of {#to_i}(8), with the provision that the base may
 *   change due to a base specification in `self` */
VALUE
rb_u_string_oct(VALUE self)
{
        return rb_u_string_to_inum(self, -8, false);
}
