/*
 * contents: UTF8.upcase module function.
 *
 * Copyright © 2006 Nikolai Weibull <now@bitwi.se>
 */

#include "rb_includes.h"

VALUE
rb_u_upcase(VALUE str)
{
        return rb_u_alloc_using(utf_upcase(StringValuePtr(str)));
}
