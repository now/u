#include "rb_includes.h"

/* @overload +(other)
 *   @param [U::String, #to_str] other
 *   @raise [ArgumentError] If {#bytesize} + OTHER{#bytesize} > LONG_MAX
 *   @return [U::String] The concatenation of OTHER to the receiver, inheriting
 *     any taint on either */
VALUE
rb_u_string_plus(VALUE self, VALUE rbother)
{
        const struct rb_u_string *string = RVAL2USTRING(self);
        const struct rb_u_string *other = RVAL2USTRING_ANY(rbother);

        long string_length = USTRING_LENGTH(string);
        long other_length = USTRING_LENGTH(other);

        /* TODO: Isn’t this off by one, as we add one to length for the
         * ALLOC_N() call? */
        if (string_length > LONG_MAX - other_length)
                rb_u_raise(rb_eArgError, "length of resulting string would be too big");
        long length = string_length + other_length;

        char *sum = ALLOC_N(char, length + 1);
        memcpy(sum, USTRING_STR(string), string_length);
        memcpy(sum + string_length, USTRING_STR(other), other_length);
        sum[length] = '\0';

        VALUE result = rb_u_string_new_uninfected_own(sum, length);
        if (OBJ_TAINTED(self) || OBJ_TAINTED(rbother))
                OBJ_TAINT(result);

        return result;
}
