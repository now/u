#include "rb_includes.h"
#include "yield.h"

static void
each(VALUE self, struct yield *yield)
{
        const struct rb_u_string *string = RVAL2USTRING(self);
        const char *q;
        const char *end = USTRING_END(string);
        for (const char *p = USTRING_STR(string); p < end; p = q) {
                q = rb_u_next_validated(p, end);
                yield_call(yield, rb_u_string_new_c(self, p, q - p));
        }
}

UNUSED(static VALUE
       size(VALUE self, UNUSED(VALUE args)))
{
        const struct rb_u_string *string = RVAL2USTRING(self);
        return UINT2NUM(u_n_chars_n(USTRING_STR(string), USTRING_LENGTH(string)));
}

/* @overload each_char{ |char| … }
 *
 *   Enumerates the characters in the receiver, each inheriting any taint and
 *   untrust.
 *
 *   @yieldparam [U::String] char
 *
 * @overload each_char
 *
 *   @return [Enumerator] An Enumerator over the characters in the receiver */
VALUE
rb_u_string_each_char(VALUE self)
{
        RETURN_SIZED_ENUMERATOR(self, 0, NULL, size);
        struct yield y = YIELD_INIT;
        each(self, &y);
        return self;
}

/* @return [Array<U::String>] The characters of the receiver, each inheriting
 *   any taint and untrust. */
VALUE
rb_u_string_chars(VALUE self)
{
        struct yield_array y = YIELD_ARRAY_INIT;
        each(self, &y.yield);
        return y.array;
}
