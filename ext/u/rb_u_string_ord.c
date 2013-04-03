#include "rb_includes.h"

/* @return [Integer] The code point of the first character of the receiver */
VALUE
rb_u_string_ord(VALUE self)
{
        const struct rb_u_string *string = RVAL2USTRING(self);
        uint32_t c = _rb_u_dref(USTRING_STR(string),
                                USTRING_END(string));

        return UINT2NUM(c);
}
