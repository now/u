#include "rb_includes.h"

VALUE
rb_u_string_bytesize(VALUE self)
{
        const UString *string = RVAL2USTRING(self);

        return LONG2NUM(USTRING_LENGTH(string));
}
