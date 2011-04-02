#include "rb_includes.h"

VALUE
rb_u_each_char(VALUE str)
{
        StringValue(str);
#if 0
        RETURN_ENUMERATOR(str, 0, 0);
#endif

        const char *s = RSTRING(str)->ptr;
        const char *s_end = s + RSTRING(str)->len;
        while (s < s_end) {
                char buf[MAX_UNICHAR_BYTE_LENGTH];
                int len = unichar_to_u(_utf_char_validated(s, s_end), buf);
                VALUE c = rb_u_new(buf, len);
                rb_yield(c);
                s = u_next(s);
        }

        return str;
}
