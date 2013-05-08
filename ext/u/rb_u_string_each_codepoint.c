#include "rb_includes.h"
#include "yield.h"

static void
each(VALUE self, struct yield *yield)
{
        const struct rb_u_string *s = RVAL2USTRING(self);
        for (const char *p = USTRING_STR(s), *end = USTRING_END(s); p < end; )
                yield_call(yield, UINT2NUM(u_decode(&p, p, end)));
}

UNUSED(static VALUE
       size(VALUE self, UNUSED(VALUE args)))
{
        const struct rb_u_string *string = RVAL2USTRING(self);
        return UINT2NUM(u_n_chars_n(USTRING_STR(string), USTRING_LENGTH(string)));
}

/* @overload each_codepoint{ |codepoint| … }
 *
 *   Enumerates the code points of the receiver.
 *
 *   @yieldparam [Integer] codepoint
 *   @return [self]
 *
 * @overload each_codepoint
 *   @return [Enumerator] An Enumerator over the code points of the receiver
 */
VALUE
rb_u_string_each_codepoint(VALUE self)
{
        RETURN_SIZED_ENUMERATOR(self, 0, NULL, size);
        struct yield y = YIELD_INIT;
        each(self, &y);
        return self;
}

/* @return [Array<Integer>] The code points of the receiver. */
VALUE
rb_u_string_codepoints(VALUE self)
{
        struct yield_array y = YIELD_ARRAY_INIT;
        each(self, &y.yield);
        return y.array;
}
