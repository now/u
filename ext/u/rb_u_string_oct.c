#include "rb_includes.h"
#include "rb_u_string_to_inum.h"

/* @return [Integer] The result of {#to_i}(8), but with the added provision
 *   that any leading base specification in the receiver will override the
 *   suggested octal (8) base, that is, `'0b11'.u`{#oct} = 3, not 9. */
VALUE
rb_u_string_oct(VALUE self)
{
        return rb_u_string_to_inum(self, -8, false);
}
