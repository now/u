#include "rb_includes.h"

/* Returns the number of bytes in this {U::String}.
 *
 * @return [Integer] The number of bytes in this {U::String} */
VALUE
rb_u_string_bytesize(VALUE self)
{
        const UString *string = RVAL2USTRING(self);

        return LONG2NUM(USTRING_LENGTH(string));
}
