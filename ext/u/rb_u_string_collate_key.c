#include "rb_includes.h"

/* Generates the locale-dependent collation key of `self`.  This key can later
 * be compared to other collation keys.  This is generally a faster way of
 * comparing {U::String}s to each other if doing so repeatedly when, for
 * example, sorting a set of {U::String}s.
 *
 * @return [U::String] The collation key of `self`
 */
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
