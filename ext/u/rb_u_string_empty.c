#include "rb_includes.h"

/* Checks if {#length} = 0.
 *
 * @return [Boolean] `True` if {#length} = 0 */
VALUE
rb_u_string_empty(VALUE self)
{
        const UString *string = RVAL2USTRING(self);

        return (USTRING_LENGTH(string) == 0) ? Qtrue : Qfalse;
}
