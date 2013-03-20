#include "rb_includes.h"

/* @overload +(other)
 *   Concatenates _other_ to this {U::String}.
 *
 *   Any taint on `self` or _other_ will be inherited by the result.
 *   @param [U::String, #to_str] other The string to concatenate to this
 *     {U::String}
 *   @raise [ArgumentError] If {#bytesize} + _other_{#bytesize} > LONG_MAX
 *   @return [U::String] The concatenation of _other_ to this {U::String} */
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

        /* TODO: Isn’t this off by one, as we add one to length for the
         * ALLOC_N() call? */
        if (string_length > LONG_MAX - other_length)
                rb_u_raise(rb_eArgError, "length of resulting string would be too big");
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
