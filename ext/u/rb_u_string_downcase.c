#include "rb_includes.h"

VALUE
rb_u_string_downcase(VALUE str)
{
        return rb_u_string_alloc_using(utf_downcase(StringValuePtr(str)));
}
