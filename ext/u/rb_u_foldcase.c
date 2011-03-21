/*
 * contents: UTF8.folcase module function.
 *
 * Copyright © 2006 Nikolai Weibull <now@bitwi.se>
 */

#include "rb_includes.h"

VALUE
rb_u_foldcase(VALUE str)
{
        return rb_u_alloc_using(utf_foldcase(StringValuePtr(str)));
}
