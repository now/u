#include "rb_includes.h"

/* @overload ascii_only?
 *   @return [Boolean] True if the receiver contains only characters in the ASCII region, that
 *     is, U+0000 through U+007F */
VALUE
rb_u_string_ascii_only(VALUE self)
{
        const UString *string = RVAL2USTRING(self);

        return u_is_ascii_only_n(USTRING_STR(string), USTRING_LENGTH(string)) ?
                Qtrue : Qfalse;
}
