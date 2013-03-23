#include "rb_includes.h"

/* @overload end_with?(*suffixes)
 *   @param [Array] suffixes
 *   @return [Boolean] True if any element of SUFFIXES that responds to #to_str
 *     is a byte-level suffix of the receiver */
VALUE
rb_u_string_end_with(int argc, VALUE *argv, VALUE self)
{
        const UString *string = RVAL2USTRING(self);
        const char *end = USTRING_END(string);
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

                if (memcmp(end - q_length, q, q_length) == 0)
                        return Qtrue;
        }

        return Qfalse;
}
