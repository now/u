#include "rb_includes.h"

VALUE
rb_u_string_starts_with(int argc, VALUE *argv, VALUE self)
{
        const UString *string = RVAL2USTRING(self);
        const char *p = USTRING_STR(string);
        long p_length = USTRING_LENGTH(string);

        for (int i = 0; i < argc; i++) {
                VALUE tmp = rb_u_string_check_type(argv[i]);
                if (NIL_P(tmp))
                        continue;

                const UString *other = RVAL2USTRING_ANY(tmp);
                const char *q = USTRING_STR(other);
                long q_length = USTRING_LENGTH(other);

                if (p_length < q_length)
                        continue;

                if (memcmp(p, q, q_length) == 0)
                        return Qtrue;
        }

        return Qfalse;
}
