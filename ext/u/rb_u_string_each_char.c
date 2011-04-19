#include "rb_includes.h"

VALUE
rb_u_string_each_char(VALUE self)
{
        RETURN_ENUMERATOR(self, 0, NULL);

        const UString *string = RVAL2USTRING(self);

        const char *p = USTRING_STR(string);
        const char *end = USTRING_END(string);
        while (p < end) {
                char buffer[MAX_UNICHAR_BYTE_LENGTH];
                int len = unichar_to_u(_rb_u_aref_char_validated(p, end), buffer);
                VALUE c = rb_u_string_new(buffer, len);

                rb_yield(c);

                p = u_next(p);
        }

        return self;
}
