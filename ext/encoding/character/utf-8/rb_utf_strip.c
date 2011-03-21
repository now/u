/*
 * contents: UTF8.strip module function.
 *
 * Copyright © 2006 Nikolai Weibull <now@bitwi.se>
 */

#include "rb_includes.h"

VALUE
rb_utf_strip_bang(VALUE str)
{
        VALUE left = rb_utf_lstrip_bang(str);
        VALUE right = rb_utf_rstrip_bang(str);

        if (NIL_P(left) && NIL_P(right))
                return Qnil;

        return str;
}

VALUE
rb_utf_strip(VALUE str)
{
        VALUE dup = rb_utf_dup(str);
        rb_utf_strip_bang(dup);

        return dup;
}
