#include "rb_includes.h"

VALUE
rb_u_string_empty(VALUE self)
{
        const UString *string = RVAL2USTRING(self);

        return (USTRING_LENGTH(string) == 0) ? Qtrue : Qfalse;
}
