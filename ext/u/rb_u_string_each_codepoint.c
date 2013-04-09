#include "rb_includes.h"
#include "yield.h"

static void
each(VALUE self, struct yield *yield)
{
        const struct rb_u_string *string = RVAL2USTRING(self);
        const char *end = USTRING_END(string);
        for (const char *p = USTRING_STR(string); p < end; p = u_next(p))
                yield_call(yield, UINT2NUM(_rb_u_dref(p, end)));
}

/* @overload each_codepoint{ |codepoint| … }
 *
 *   Enumerates the code points of the receiver.
 *
 *   @yieldparam [Integer] codepoint
 *
 * @overload each_codepoint
 *   @return [Enumerator] An Enumerator over the code points of the receiver
 */
VALUE
rb_u_string_each_codepoint(VALUE self)
{
        RETURN_ENUMERATOR(self, 0, NULL);
        struct yield y = YIELD_INIT;
        each(self, &y);
        return self;
}

/* @return [Array<U::String>] The code points of the receiver. */
VALUE
rb_u_string_codepoints(VALUE self)
{
        struct yield_array y = YIELD_ARRAY_INIT;
        each(self, &y.yield);
        return y.array;
}
