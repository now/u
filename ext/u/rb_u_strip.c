#include "rb_includes.h"

VALUE
rb_u_strip_bang(VALUE str)
{
        VALUE left = rb_u_lstrip_bang(str);
        VALUE right = rb_u_rstrip_bang(str);

        if (NIL_P(left) && NIL_P(right))
                return Qnil;

        return str;
}

VALUE
rb_u_strip(VALUE str)
{
        VALUE dup = rb_u_dup(str);
        rb_u_strip_bang(dup);

        return dup;
}
