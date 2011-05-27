#include "rb_includes.h"

VALUE
rb_u_string_ord(VALUE self)
{
        const UString *string = RVAL2USTRING(self);
        unichar c = _rb_u_aref_char_validated(USTRING_STR(string),
                                              USTRING_END(string));

        return UINT2NUM(c);
}
