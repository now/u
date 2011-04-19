#include "rb_includes.h"

VALUE
rb_u_string_plus(VALUE self, VALUE rbother)
{
        const UString *string = RVAL2USTRING(self);
        const UString *other = RVAL2USTRING_ANY(rbother);

        long string_length = USTRING_LENGTH(string);
        if (string_length == 0)
                return rbother;

        long other_length = USTRING_LENGTH(other);
        if (other_length == 0)
                return self;

        long length = string_length + other_length;
        char *sum = ALLOC_N(char, length + 1);
        memcpy(sum, USTRING_STR(string), string_length);
        memcpy(sum + string_length, USTRING_STR(other), other_length);
        sum[length] = '\0';

        VALUE result = rb_u_string_new_own(sum, length);
        if (OBJ_TAINTED(self) || OBJ_TAINTED(rbother))
                OBJ_TAINT(result);

        return result;
}