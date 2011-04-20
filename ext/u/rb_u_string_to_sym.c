#include "rb_includes.h"

VALUE
rb_u_string_to_sym(VALUE self)
{
        /* NOTE: Lazy, but MRI makes it hard to implement this method. */
        return rb_str_intern(StringValue(self));
}
