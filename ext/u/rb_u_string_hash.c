#include "rb_includes.h"

/* @return [Fixnum] The hash value of the receiver’s content */
VALUE
rb_u_string_hash(VALUE self)
{
        const struct rb_u_string *string = RVAL2USTRING(self);

        return INT2FIX(rb_memhash(USTRING_STR(string), USTRING_LENGTH(string)));
}
