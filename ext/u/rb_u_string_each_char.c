#include "rb_includes.h"

/* @overload each_char{ |char| … }
 *
 *   Enumerates the characters in the receiver, each inheriting any taint or
 *   untrust.
 *
 *   @yieldparam [U::String] char
 *
 * @overload each_char
 *
 *   @return [Enumerator] An Enumerator over the characters in the receiver
 */
VALUE
rb_u_string_each_char(VALUE self)
{
        RETURN_ENUMERATOR(self, 0, NULL);

        const UString *string = RVAL2USTRING(self);

        const char *p = USTRING_STR(string);
        const char *end = USTRING_END(string);
        while (p < end) {
                const char *q = rb_u_next_validated(p, end);
                VALUE c = rb_u_string_new(p, q - p);

                OBJ_INFECT(c, self);
                rb_yield(c);

                p = u_next(p);
        }

        return self;
}
