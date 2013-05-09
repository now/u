#include "rb_includes.h"

static void
each(const char *p, size_t n, VALUE *self)
{
        rb_yield(rb_u_string_new_c(*self, p, n));
}

/* @overload each_grapheme_cluster{ |cluster| … }
 *
 *   Enumerates the grapheme clusters in the receiver, each inheriting any
 *   taint and untrust.
 *
 *   @yieldparam [U::String] cluster
 *   @return [self]
 *   @see http://www.unicode.org/reports/tr29/
 *     Unicode Standard Annex #29: Unicode Text Segmentation
 *
 * @overload each_grapheme_cluster
 *
 *   @return [Enumerator] An Enumerator over the grapheme clusters in the
 *     receiver
 *   @see http://www.unicode.org/reports/tr29/
 *     Unicode Standard Annex #29: Unicode Text Segmentation */
VALUE
rb_u_string_each_grapheme_cluster(VALUE self)
{
        RETURN_ENUMERATOR(self, 0, NULL);

        const struct rb_u_string *string = RVAL2USTRING(self);
        const char *p = USTRING_STR(string);
        const char *end = USTRING_END(string);
        size_t length = end - p;
        u_grapheme_clusters(p, length, (u_substring_fn)each, &self);
        return self;
}
