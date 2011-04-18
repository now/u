#include "rb_includes.h"

VALUE
rb_u_string_each_byte(VALUE self)
{
        const UString *string = RVAL2USTRING(self);

        RETURN_ENUMERATOR(self, 0, 0);

        const char *p = USTRING_STR(string);
        const char *end = USTRING_END(string);
        while (p < end) {
                rb_yield(INT2FIX(*p & 0xff));
                p++;
        }

        return self;
}
