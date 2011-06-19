#include "rb_includes.h"

VALUE
rb_u_string_width(VALUE self)
{
        const UString *string = RVAL2USTRING(self);

        return UINT2NUM(u_width_n(USTRING_STR(string), USTRING_LENGTH(string)));
}
