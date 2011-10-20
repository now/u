#include "rb_includes.h"

/* Tests if this {U::String} only contains characters in the ASCII region, that
 * is, U+0000 through U+007F.
 *
 * @return [Boolean] `True` if this {U::String} only contains characters in the
 *   ASCII region. */
VALUE
rb_u_string_ascii_only(VALUE self)
{
        const UString *string = RVAL2USTRING(self);

        return u_is_ascii_only_n(USTRING_STR(string), USTRING_LENGTH(string)) ?
                Qtrue : Qfalse;
}
