#include "rb_includes.h"

VALUE
rb_u_string_ascii_only(VALUE self)
{
        const UString *string = RVAL2USTRING(self);

        return u_is_ascii_only_n(USTRING_STR(string), USTRING_LENGTH(string)) ?
                Qtrue : Qfalse;
}
