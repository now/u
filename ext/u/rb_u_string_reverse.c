#include "rb_includes.h"

VALUE
rb_u_string_reverse(VALUE self)
{
        const UString *string = RVAL2USTRING(self);
        long length = USTRING_LENGTH(string);

        char *reversed = u_reverse_n(USTRING_STR(string), length);

        return rb_u_string_new_own(reversed, length);
}
