#include "rb_includes.h"

/* @return [U::String] The case-folding of the receiver, inheriting any taint
 *   and untrust */
VALUE
rb_u_string_foldcase(VALUE self)
{
        const struct rb_u_string *string = RVAL2USTRING(self);

        size_t length;
        char *folded = u_foldcase_n(USTRING_STR(string),
                                    USTRING_LENGTH(string),
                                    &length);

        return rb_u_string_new_c_own(self, folded, length);
}
