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
        const char *q = end;
        while (begin < q) {
                const char *p;
                uint32_t c = u_decode_r(&p, begin, q);
                if (c != '\0' && !u_char_isspace(c))
                        break;
                q = p;
        }
        if (q == end)
                return self;

        return rb_u_string_new_c(self, begin, q - begin);
}
