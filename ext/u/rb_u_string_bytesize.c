#include "rb_includes.h"

/* @return [Integer] The number of bytes required to represent the receiver */
VALUE
rb_u_string_bytesize(VALUE self)
{
        const struct rb_u_string *string = RVAL2USTRING(self);

        return LONG2NUM(USTRING_LENGTH(string));
}
