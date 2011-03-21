/*
 * contents: UTF8.upcase module function.
 *
 * Copyright © 2006 Nikolai Weibull <now@bitwi.se>
 */

#include "rb_includes.h"

VALUE
rb_utf_upcase(VALUE str)
{
        return rb_utf_alloc_using(utf_upcase(StringValuePtr(str)));
}
