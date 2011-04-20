#include "rb_includes.h"

VALUE
rb_u_string_ends_with(int argc, VALUE *argv, VALUE self)
{
        const UString *string = RVAL2USTRING(self);

        for (int i = 0; i < argc; i++) {
                VALUE tmp = rb_u_string_check_type(argv[i]);
                if (NIL_P(tmp))
                        continue;

                const UString *other = RVAL2USTRING_ANY(tmp);

                if (USTRING_LENGTH(string) < USTRING_LENGTH(other))
                        continue;

                if (memcmp(USTRING_END(string) - USTRING_LENGTH(other),
                           USTRING_STR(other),
                           USTRING_LENGTH(other)) == 0)
                        return Qtrue;
        }

        return Qfalse;
}
