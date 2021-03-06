#include "rb_includes.h"

/* @return [Integer] The code point of the first character of the receiver */
VALUE
rb_u_string_ord(VALUE self)
{
        const struct rb_u_string *s = RVAL2USTRING(self);
        const char *p = USTRING_STR(s);
        const char *end = USTRING_END(s);
        if (p == end)
                rb_u_raise(rb_eArgError, "empty string");
        const char *q;
        return UINT2NUM(u_decode(&q, p, end));
}
