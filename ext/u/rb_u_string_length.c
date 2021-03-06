#include "rb_includes.h"

/* @return [Integer] The number of characters in the receiver */
VALUE
rb_u_string_length(VALUE self)
{
        const struct rb_u_string *string = RVAL2USTRING(self);

        return UINT2NUM(u_n_chars_n(USTRING_STR(string), USTRING_LENGTH(string)));
}
