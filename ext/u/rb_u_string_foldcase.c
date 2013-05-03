#include "rb_includes.h"

/* @return [U::String] The case-folding of the receiver, inheriting any taint
 *   and untrust */
VALUE
rb_u_string_foldcase(VALUE self)
{
        const struct rb_u_string *string = RVAL2USTRING(self);

        size_t n = u_foldcase(NULL, 0,
                              USTRING_STR(string), USTRING_LENGTH(string));
        char *folded = ALLOC_N(char, n + 1);
        u_foldcase(folded, n + 1,
                   USTRING_STR(string), USTRING_LENGTH(string));

        return rb_u_string_new_c_own(self, folded, n);
}
