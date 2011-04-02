#include "rb_includes.h"

VALUE
rb_u_string_foldcase(VALUE str)
{
        return rb_u_string_alloc_using(utf_foldcase(StringValuePtr(str)));
}
