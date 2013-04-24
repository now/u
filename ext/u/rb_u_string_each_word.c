#include "rb_includes.h"

static void
each(const char *p, size_t n, VALUE *self)
{
        rb_yield(rb_u_string_new_c(*self, p, n));
}

/* @overload each_word{ |word| … }
 *
 *   Enumerates the words in the receiver, each inheriting any taint and
 *   untrust.
 *
 *   @yieldparam [U::String] word
 *   @return [self]
 *   @see http://www.unicode.org/reports/tr29/
 *     Unicode Standard Annex #29: Unicode Text Segmentation
 *
 * @overload each_word
 *
 *   @return [Enumerator] An Enumerator over the characters in the receiver
 *   @see http://www.unicode.org/reports/tr29/
 *     Unicode Standard Annex #29: Unicode Text Segmentation */
VALUE
rb_u_string_each_word(VALUE self)
{
        RETURN_ENUMERATOR(self, 0, NULL);

        const struct rb_u_string *string = RVAL2USTRING(self);
        const char *p = USTRING_STR(string);
        size_t length = USTRING_LENGTH(string);
        rb_u_validate(p, length);
        u_words(p, length, (u_substring_fn)each, &self);
        return self;
}
