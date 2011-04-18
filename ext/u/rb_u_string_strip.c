#include "rb_includes.h"

VALUE
rb_u_string_strip(VALUE self)
{
        const UString *string = RVAL2USTRING(self);

        const char *begin = USTRING_STR(string);
        if (begin == NULL)
                return self;

        const char *end = USTRING_END(string);
        const char *s = begin;
        while (s < end && unichar_isspace(_rb_u_aref_char_validated(s, end)))
                s = u_next(s);

        const char *t = end;
        while (t > begin) {
                const char *prev = rb_u_prev_validated(begin, t);
                unichar c = u_aref_char(prev);

                if (c != '\0' && !unichar_isspace(c))
                        break;

                t = prev;
        }

        if (s == begin && t == end)
                return self;

        return rb_u_string_new(s, t - s);
}
