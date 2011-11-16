#include "rb_includes.h"

/* Enumerates each character in this {U::String}.
 *
 * @overload each_char{ |char| … }
 *
 *   Enumerate each character in this {U::String}.
 *
 *   Any taint or untrust is inherited.
 *
 *   @yieldparam [U::String] char Character at current position
 *   @return [U::String] `self`
 *
 * @overload each_char
 *
 *   Creates an Enumerator over each character in this {U::String}.
 *
 *   Any taint or untrust is inherited.
 *
 *   @return [Enumerator] An Enumerator over each character in this {U::String}
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
