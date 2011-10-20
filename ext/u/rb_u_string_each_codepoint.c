#include "rb_includes.h"

/* @overload codepoints{ |codepoint| … }
 * @overload each_codepoint{ |codepoint| … }
 *
 *   Enumerate each codepoint in this {U::String}.
 *
 *   @yield [codepoint] Enumerate each codepoint in this {U::String}
 *   @yieldparam [Integer] codepoint Codepoint at current position
 *   @return [U::String] `self`
 *
 * @overload codepoints
 * @overload each_codepoints
 *
 *   Creates an Enumerator over each codepoint in this {U::String}.
 *
 *   @return [Enumerator] An Enumerator over each codepoint in this {U::String}
 */
VALUE
rb_u_string_each_codepoint(VALUE self)
{
        RETURN_ENUMERATOR(self, 0, NULL);

        const UString *string = RVAL2USTRING(self);

        const char *p = USTRING_STR(string);
        const char *end = USTRING_END(string);
        while (p < end) {
                rb_yield(UINT2NUM(_rb_u_aref_char_validated(p, end)));

                p = u_next(p);
        }

        return self;
}
