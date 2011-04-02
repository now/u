#include "rb_includes.h"

VALUE
rb_u_string_chop_bang(VALUE str)
{
        StringValue(str);

        if (RSTRING(str)->len == 0)
                return Qnil;

        rb_str_modify(str);

        const char *end = RSTRING(str)->ptr + RSTRING(str)->len;

        char *last = rb_u_prev_validated(RSTRING(str)->ptr, end);

        if (_utf_char_validated(last, end) == '\n') {
                char *last_but_one = u_find_prev(RSTRING(str)->ptr, last);

                if (last_but_one != NULL && u_aref_char(last_but_one) == '\r')
                        last = last_but_one;
        } else if (!unichar_isnewline(u_aref_char(last))) {
                return Qnil;
        }

        RSTRING(str)->len -= (RSTRING(str)->ptr + RSTRING(str)->len) - last;
        *last = '\0';

        return str;
}

VALUE
rb_u_string_chop(VALUE str)
{
        StringValue(str);

        VALUE dup = rb_u_string_dup(str);
        rb_u_string_chop_bang(dup);

        return dup;
}
