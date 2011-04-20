#include "rb_includes.h"

VALUE
rb_u_string_include(VALUE self, VALUE other)
{
        return rb_u_string_index(self, other, 0) != -1 ? Qtrue : Qfalse;
}
