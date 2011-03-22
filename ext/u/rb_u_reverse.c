/*
 * contents: UTF8.reverse module function.
 *
 * Copyright © 2006 Nikolai Weibull <now@bitwi.se>
 */

#include "rb_includes.h"

VALUE
rb_u_reverse(VALUE str)
{
        return rb_u_alloc_using(u_reverse(StringValuePtr(str)));
}
