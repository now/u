#include "rb_includes.h"

VALUE
rb_u_string_getbyte(VALUE self, VALUE rbindex)
{
        const UString *string = RVAL2USTRING(self);
        long index = NUM2LONG(rbindex);

        if (index < 0)
                index += USTRING_LENGTH(string);

        if (index < 0 || USTRING_LENGTH(string) <= index)
                return Qnil;

        return INT2FIX((unsigned char)USTRING_STR(string)[index]);
}
