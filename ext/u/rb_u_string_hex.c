#include "rb_includes.h"
#include "rb_u_string_internal_bignum.h"

VALUE
rb_u_string_hex(VALUE self)
{
        return rb_u_string_to_inum(self, 16, false);
}
