#include "rb_includes.h"
#include "yield.h"

static void
each(VALUE self, struct yield *yield)
{
        const struct rb_u_string *string = RVAL2USTRING(self);
        const char *end = USTRING_END(string);
        for (const char *p = USTRING_STR(string); p < end; p++)
                yield_call(yield, INT2FIX(*p & 0xff));
}

UNUSED(static VALUE
       size(VALUE self, UNUSED(VALUE args)))
{
        return LONG2NUM(USTRING_LENGTH(RVAL2USTRING(self)));
}

/* @overload each_byte{ |byte| … }
 *
 *   Enumerates the bytes in the receiver.
 *
 *   @yieldparam [Fixnum] byte
 *
 * @overload each_byte
 *
 *   @return [Enumerator] An Enumerator over the bytes in the receiver
 */
VALUE
rb_u_string_each_byte(VALUE self)
{
        RETURN_SIZED_ENUMERATOR(self, 0, NULL, size);
        struct yield y = YIELD_INIT;
        each(self, &y);
        return self;
}

/* @return [Array<Fixnum>] The bytes of the receiver. */
VALUE
rb_u_string_bytes(VALUE self)
{
        struct yield_array y = YIELD_ARRAY_INIT;
        each(self, &y.yield);
        return y.array;
}
