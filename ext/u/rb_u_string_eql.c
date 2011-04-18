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

        return u_collate_n(USTRING_STR(string), USTRING_LENGTH(string),
                           USTRING_STR(other), USTRING_LENGTH(other)) == 0 ?
                Qtrue : Qfalse;
}
