#include "rb_includes.h"

VALUE
rb_u_string_reverse(VALUE str)
{
        return rb_u_string_alloc_using(u_reverse(StringValuePtr(str)));
}
