/*
 * contents: UTF8.hex module function.
 *
 * Copyright © 2006 Nikolai Weibull <now@bitwi.se>
 */

#include "rb_includes.h"
#include "rb_u_internal_bignum.h"

VALUE
rb_u_hex(VALUE str)
{
        return rb_u_to_inum(str, 16, false);
}
