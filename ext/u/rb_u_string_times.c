#include "rb_includes.h"

/* @overload *(n)
 *   @param [Integer] n
 *   @raise [ArgumentError] If N < 0
 *   @raise [ArgumentError] If N > 0 and N × {#bytesize} > LONG_MAX
 *   @return [U::String] The concatenation of N copies of the receiver,
 *     inheriting any taint and untrust */
VALUE
rb_u_string_times(VALUE self, VALUE rbtimes)
{
        const UString *string = RVAL2USTRING(self);

        long times = NUM2LONG(rbtimes);
        if (times < 0)
                rb_u_raise(rb_eArgError, "negative argument: %ld", times);

        /* TODO: Isn’t this off by one, as we add one to length for the
         * ALLOC_N() call? */
        if (times > 0 && LONG_MAX / times < USTRING_LENGTH(string))
                rb_u_raise(rb_eArgError, "argument too big: %ld", times);
        long length = times * USTRING_LENGTH(string);

        char *product = ALLOC_N(char, length + 1);
        long i = USTRING_LENGTH(string);
        memcpy(product, USTRING_STR(string), i);
        for ( ; i <= times / 2; i *= 2)
                memcpy(product + i, product, i);
        memcpy(product + i, product, times - i);
        product[length] = '\0';

        VALUE result = rb_u_string_new_own(product, length);
        OBJ_INFECT(result, self);

        return result;
}
