#include "rb_includes.h"

/* @overload valid_encoding?
 *   @return [Boolean] True if the receiver contains only valid UTF-8
 *     sequences */
VALUE
rb_u_string_valid_encoding(VALUE self)
{
        const UString *string = RVAL2USTRING(self);

        return u_isvalid_n(USTRING_STR(string), USTRING_LENGTH(string), NULL) ? Qtrue : Qfalse;
}
