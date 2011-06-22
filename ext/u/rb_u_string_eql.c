#include "rb_includes.h"

VALUE
rb_u_string_eql(VALUE self, VALUE rbother)
{
        if (self == rbother)
                return Qtrue;

        if (!rb_obj_is_kind_of(rbother, rb_cUString))
                return Qfalse;

        const UString *string = RVAL2USTRING(self);
        const UString *other = RVAL2USTRING(rbother);

        const char *p = USTRING_STR(string);
        const char *q = USTRING_STR(other);

        if (p == q)
                return Qtrue;

        long p_length = USTRING_LENGTH(string);
        long q_length = USTRING_LENGTH(other);

        return p_length == q_length && memcmp(p, q, q_length) == 0 ? Qtrue : Qfalse;
}
