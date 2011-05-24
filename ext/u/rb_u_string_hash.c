#include "rb_includes.h"

VALUE
rb_u_string_hash(VALUE self)
{
        const UString *string = RVAL2USTRING(self);

        return INT2FIX(rb_memhash(USTRING_STR(string), USTRING_LENGTH(string)));
}
