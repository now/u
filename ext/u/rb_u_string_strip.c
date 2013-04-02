#include "rb_includes.h"

/* @return [U::String] The receiver with its maximum {#space?} prefix and
 *   suffix removed, inheriting any taint and untrust
 * @see #lstrip
 * @see #rstrip */
VALUE
rb_u_string_strip(VALUE self)
{
        const struct rb_u_string *string = RVAL2USTRING(self);

        const char *begin = USTRING_STR(string);
        if (begin == NULL)
                return self;

        const char *end = USTRING_END(string);
        const char *s = begin;
        while (s < end && u_char_isspace(_rb_u_aref_char_validated(s, end)))
                s = u_next(s);

        const char *t = end;
        while (t > begin) {
                const char *prev = rb_u_prev_validated(begin, t);
                uint32_t c = u_dref(prev);

                if (c != '\0' && !u_char_isspace(c))
                        break;

                t = prev;
        }

        if (s == begin && t == end)
                return self;

        return rb_u_string_new_c(self, s, t - s);
}
