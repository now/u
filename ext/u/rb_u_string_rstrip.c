#include "rb_includes.h"

VALUE
rb_u_string_rstrip_bang(VALUE str)
{
        StringValue(str);
        const char *begin = RSTRING(str)->ptr;
        if (begin == NULL || RSTRING(str)->len == 0)
                return Qnil;

        const char *end = begin + RSTRING(str)->len;
        const char *t = end;

        /* Remove trailing '\0'’s. */
        while (t > begin && t[-1] == '\0')
                t--;

        /* Remove trailing spaces. */
        while (t > begin) {
                /* FIXME: Should we be validating here? */
                const char *prev = rb_u_prev_validated(begin, t);

                if (!unichar_isspace(u_aref_char(prev)))
                        break;

                t = prev;
        }

        if (t == end)
                return Qnil;

        rb_str_modify(str);
        RSTRING(str)->len = t - begin;
        RSTRING(str)->ptr[RSTRING(str)->len] = '\0';

        return str;
}

VALUE
rb_u_string_rstrip(VALUE str)
{
        VALUE dup = rb_u_string_dup(str);
        rb_u_string_rstrip_bang(dup);

        return dup;
}
