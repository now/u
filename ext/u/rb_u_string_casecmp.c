#include "rb_includes.h"

VALUE
rb_u_string_casecmp(VALUE self, VALUE rbother)
{
        const UString *string = RVAL2USTRING(self);
        const UString *other = RVAL2USTRING_ANY(rbother);

        size_t folded_length;
        char *folded = utf_foldcase_n(USTRING_STR(string),
                                      USTRING_LENGTH(string),
                                      &folded_length);

        size_t folded_other_length;
        char *folded_other = utf_foldcase_n(USTRING_STR(other),
                                            USTRING_LENGTH(other),
                                            &folded_other_length);

        int result = u_collate_n(folded, folded_length,
                                 folded_other, folded_other_length);

        free(folded_other);
        free(folded);

        return INT2FIX(result);
}
