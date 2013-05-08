#include "rb_includes.h"

/* @return [U::String] The receiver with its maximum {#space?} suffix removed,
 *   inheriting any taint and untrust from the receiver
 * @see #lstrip
 * @see #strip */
VALUE
rb_u_string_rstrip(VALUE self)
{
        const struct rb_u_string *string = RVAL2USTRING(self);

        const char *begin = USTRING_STR(string);
        if (begin == NULL)
                return self;

        const char *end = USTRING_END(string);
        const char *p = end;
        while (p > begin) {
                const char *prev = rb_u_prev_validated(begin, p);
                uint32_t c;
                u_decode(&c, prev, end);

                if (c != '\0' && !u_char_isspace(c))
                        break;

                p = prev;
        }
        if (p == end)
                return self;

        return rb_u_string_new_c(self, begin, p - begin);
}
