#include "rb_includes.h"

struct closure {
        VALUE self;
        const char *previous;
};

static inline void
yield(const char *p, struct closure *closure)
{
        rb_yield(rb_u_string_new_c(closure->self,
                                   closure->previous,
                                   p - closure->previous));
}

static void
each(const char *p, struct closure *closure)
{
        if (p != closure->previous)
                yield(p, closure);
        closure->previous = p;
}

/* @overload each_grapheme_cluster{ |cluster| … }
 *
 *   Enumerates the grapheme clusters in the receiver, each inheriting any
 *   taint and untrust.
 *
 *   @yieldparam [U::String] cluster
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
        rb_u_validate(p, length);
        struct closure closure = { self, p };
        u_grapheme_breaks(p, length, (UnicodeBreakFn)each, &closure);
        if (closure.previous != end)
                yield(end, &closure);
        return self;
}
