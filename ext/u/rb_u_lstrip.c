/*
 * contents: UTF8.lstrip module function.
 *
 * Copyright © 2006 Nikolai Weibull <now@bitwi.se>
 */

#include "rb_includes.h"

VALUE
rb_u_lstrip_bang(VALUE str)
{
        StringValue(str);
        char *s = RSTRING(str)->ptr;
        if (s == NULL || RSTRING(str)->len == 0)
                return Qnil;

        char *end = s + RSTRING(str)->len;

        /* Remove spaces at head. */
        while (s < end && unichar_isspace(_utf_char_validated(s, end)))
                s = utf_next(s);

        /* If there weren’t any spaces at head, return Qnil. */
        if (s == RSTRING(str)->ptr)
                return Qnil;

        rb_str_modify(str);
        RSTRING(str)->len = end - s;
        memmove(RSTRING(str)->ptr, s, RSTRING(str)->len);
        RSTRING(str)->ptr[RSTRING(str)->len] = '\0';

        return str;
}

VALUE
rb_u_lstrip(VALUE str)
{
        VALUE dup = rb_u_dup(str);
        rb_u_lstrip_bang(dup);

        return dup;
}
