#include "rb_includes.h"

VALUE
rb_u_string_foldcase(VALUE self)
{
        const UString *string = RVAL2USTRING(self);

        size_t length;
        char *folded = utf_foldcase_n(USTRING_STR(string),
                                      USTRING_LENGTH(string),
                                      &length);

        return rb_u_string_new_own(folded, length);
}
