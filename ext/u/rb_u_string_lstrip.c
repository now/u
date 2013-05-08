#include "rb_includes.h"

/* @return [U::String] The receiver with its maximum {#space?} prefix removed,
 *   inheriting any taint and untrust
 * @see #rstrip
 * @see #strip */
VALUE
rb_u_string_lstrip(VALUE self)
{
        const struct rb_u_string *string = RVAL2USTRING(self);

        const char *begin = USTRING_STR(string);
        if (begin == NULL)
                return self;

        const char *p = begin, *end = USTRING_END(string);
        while (p < end) {
                uint32_t c;
                const char *q = u_decode(&c, p, end);
                if (!u_char_isspace(c))
                        break;
                p = q;
        }
        if (p == begin)
                return self;

        return rb_u_string_new_c(self, p, end - p);
}
