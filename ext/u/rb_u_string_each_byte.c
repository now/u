#include "rb_includes.h"

/* @overload each_byte{ |byte| … }
 *
 *   Enumerates the bytes in the receiver.
 *
 *   @yieldparam [Fixnum] byte
 *
 * @overload each_byte
 *
 *   @return [Enumerator] An Enumerator over the bytes in the receiver
 */
VALUE
rb_u_string_each_byte(VALUE self)
{
        RETURN_ENUMERATOR(self, 0, NULL);

        const UString *string = RVAL2USTRING(self);

        const char *p = USTRING_STR(string);
        const char *end = USTRING_END(string);
        while (p < end) {
                rb_yield(INT2FIX(*p & 0xff));
                p++;
        }

        return self;
}
