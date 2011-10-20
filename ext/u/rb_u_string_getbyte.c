#include "rb_includes.h"

/* @overload getbyte(index)
 *
 * Gets the byte at index _i_, where _i_ = _index_ if _index_ ≥ 0, _i_ =
 * {#length} - abs(_index_) otherwise.
 *
 * @param [Integer] index Byte index of byte to get
 * @return [Fixnum, nil] The byte at byte _index_, or nil if _i_ lays outside
 *   of the possible indexes into `self` */
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
