#include "rb_includes.h"

VALUE
rb_u_string_folded(VALUE self)
{
        return _rb_u_string_test(self, u_foldcase_n);
}
