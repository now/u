#include "rb_includes.h"

/* @overload start_with?(*prefixes)
 *   @param [Array] prefixes
 *   @return [Boolean] True if any element of PREFIXES that responds to #to_str
 *     is a byte-level prefix of the receiver */
VALUE
rb_u_string_start_with(int argc, VALUE *argv, VALUE self)
{
        const struct rb_u_string *string = RVAL2USTRING(self);
        const char *p = USTRING_STR(string);
        long p_length = USTRING_LENGTH(string);

        for (int i = 0; i < argc; i++) {
                VALUE tmp = rb_u_string_check_type(argv[i]);
                if (NIL_P(tmp))
                        continue;

                const struct rb_u_string *other = RVAL2USTRING_ANY(tmp);
                const char *q = USTRING_STR(other);
                long q_length = USTRING_LENGTH(other);

                if (p_length < q_length)
                        continue;

                if (memcmp(p, q, q_length) == 0)
                        return Qtrue;
        }

        return Qfalse;
}
