#include "rb_includes.h"

/* @overload empty?
 *   @return [Boolean] True if {#bytesize} = 0 */
VALUE
rb_u_string_empty(VALUE self)
{
        const struct rb_u_string *string = RVAL2USTRING(self);

        return (USTRING_LENGTH(string) == 0) ? Qtrue : Qfalse;
}
