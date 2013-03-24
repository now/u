#include "rb_includes.h"

/* @return [U::String] The locale-dependent collation key of the receiver,
 *   inheriting any taint and untrust
 * @note Use the collation key when comparing U::Strings to each other
 *   repeatedly, as occurs when, for example, sorting a list of U::Strings */
VALUE
rb_u_string_collate_key(VALUE self)
{
        const UString *string = RVAL2USTRING(self);

        size_t length;
        char *collate_key = u_collate_key_n(USTRING_STR(string),
                                            USTRING_LENGTH(string),
                                            &length);

        return rb_u_string_new_c_own(self, collate_key, length);
}
