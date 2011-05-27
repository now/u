#include "rb_includes.h"

VALUE
rb_u_string_chr(VALUE self)
{
        return rb_u_string_substr(self, 0, 1);
}
