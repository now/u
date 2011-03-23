/*
 * contents: UTF8.length module function.
 *
 * Copyright © 2006 Nikolai Weibull <now@bitwi.se>
 */

#include "rb_includes.h"

VALUE
rb_u_length(VALUE str)
{
        StringValue(str);

        return UINT2NUM(u_length_n(RSTRING(str)->ptr, RSTRING(str)->len));
}