#include "rb_includes.h"

/* @return The String representation of the receiver, inheriting any taint and
 *   untrust */
VALUE
rb_u_string_to_str(VALUE self)
{
        const UString *string = RVAL2USTRING(self);

        VALUE result = NIL_P(string->rb) ?
                rb_u_str_new(USTRING_STR(string), USTRING_LENGTH(string)) :
                string->rb;

        OBJ_INFECT(result, self);

        return result;
}
