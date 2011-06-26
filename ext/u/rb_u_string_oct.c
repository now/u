#include "rb_includes.h"
#include "rb_u_string_to_inum.h"

VALUE
rb_u_string_oct(VALUE self)
{
        return rb_u_string_to_inum(self, -8, false);
}
