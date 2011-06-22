#include "rb_includes.h"

VALUE
rb_u_string_combining_class(VALUE self)
{
        int current = -1;

        const UString *string = RVAL2USTRING(self);

        const char *p = USTRING_STR(string);
        const char *end = USTRING_END(string);
        while (p < end) {
                int combining_class = unichar_combining_class(u_aref_char_validated_n(p, end - p));

                if (current == -1)
                        current = combining_class;
                else if (combining_class != current)
                        rb_raise(rb_eArgError,
                                 "string consists of more than one combining class: %d+, %d",
                                 current,
                                 combining_class);

                p = u_next(p);
        }

        return INT2FIX(current);
}
