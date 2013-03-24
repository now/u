#include "rb_includes.h"

/* @return [U::String] The receiver with its maximum {#space?} suffix removed,
 *   inheriting any taint and untrust from the receiver
 * @see #lstrip
 * @see #strip */
VALUE
rb_u_string_rstrip(VALUE self)
{
        const UString *string = RVAL2USTRING(self);

        const char *begin = USTRING_STR(string);
        if (begin == NULL)
                return self;

        const char *end = USTRING_END(string);
        const char *p = end;
        while (p > begin) {
                const char *prev = rb_u_prev_validated(begin, p);
                unichar c = u_aref_char(prev);

                if (c != '\0' && !unichar_isspace(c))
                        break;

                p = prev;
        }
        if (p == end)
                return self;

        return rb_u_string_new_c(self, begin, p - begin);
}
