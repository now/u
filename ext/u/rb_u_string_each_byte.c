#include "rb_includes.h"

/* @overload each_byte{ |byte| … }
 *
 *   Enumerate each byte in this {U::String}.
 *
 *   @yield [byte] Enumerate each byte in this {U::String}
 *   @yieldparam [Fixnum] byte Byte at current position
 *   @return [U::String] `self`
 *
 * @overload each_byte
 *
 *   Creates an Enumerator over each byte in this {U::String}.
 *
 *   @return [Enumerator] An Enumerator over each byte in this {U::String}
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
