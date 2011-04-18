#include "rb_includes.h"

VALUE
rb_u_string_collate(VALUE self, VALUE rbother)
{
        const UString *string = RVAL2USTRING(self);
        const UString *other = RVAL2USTRING_ANY(rbother);

        return INT2FIX(u_collate_n(USTRING_STR(string), USTRING_LENGTH(string),
                                   USTRING_STR(other), USTRING_LENGTH(other)));
}
