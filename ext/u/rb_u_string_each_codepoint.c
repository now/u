#include "rb_includes.h"

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
