#include "rb_includes.h"

VALUE
rb_u_string_collate_key(VALUE self)
{
        const UString *string = RVAL2USTRING(self);

        size_t length;
        char *collate_key = u_collate_key_n(USTRING_STR(string),
                                            USTRING_LENGTH(string),
                                            &length);

        return rb_u_string_new_own(collate_key, length);
}
