#include "rb_includes.h"

/* Extracts the codepoint of the first character in this {U::String}.
 *
 * @return [Integer] Codepoint of first character in this {U::String} */
VALUE
rb_u_string_ord(VALUE self)
{
        const UString *string = RVAL2USTRING(self);
        unichar c = _rb_u_aref_char_validated(USTRING_STR(string),
                                              USTRING_END(string));

        return UINT2NUM(c);
}
