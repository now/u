#include "rb_includes.h"

/* @overload getbyte(index)
 *   @param [#to_int] index
 *   @return [Fixnum, nil] The byte at byte-index _i_, where _i_ = INDEX if
 *     INDEX ≥ 0, _i_ = {#bytesize} - abs(INDEX) otherwise, or nil if _i_ lays
 *     outside of [0, {#bytesize}] */
VALUE
rb_u_string_getbyte(VALUE self, VALUE rbindex)
{
        const struct rb_u_string *string = RVAL2USTRING(self);
        long index = NUM2LONG(rbindex);

        if (index < 0)
                index += USTRING_LENGTH(string);

        if (index < 0 || USTRING_LENGTH(string) <= index)
                return Qnil;

        return INT2FIX((unsigned char)USTRING_STR(string)[index]);
}
