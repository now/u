#include "rb_includes.h"

/* Case folds this {U::String}.
 *
 * @return [U::String] A case-folded version of `self` */
VALUE
rb_u_string_foldcase(VALUE self)
{
        const UString *string = RVAL2USTRING(self);

        size_t length;
        char *folded = u_foldcase_n(USTRING_STR(string),
                                    USTRING_LENGTH(string),
                                    &length);

        return rb_u_string_new_own(folded, length);
}
