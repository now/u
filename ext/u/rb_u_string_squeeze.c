#include "rb_includes.h"
#include "rb_u_string_internal_tr.h"

static long
rb_u_string_squeeze_loop(const UString *string, struct tr_table *table,
                         char *result)
{
        long count = 0;

        const char *p = USTRING_STR(string);
        const char *end = USTRING_END(string);

        unichar previous = UNICODE_N_CODEPOINTS;
        char *base = result;
        while (p < end) {
                unichar c = _rb_u_aref_char_validated(p, end);
                const char *next = u_next(p);

                if (c != previous ||
                    (table != NULL && !tr_table_lookup(table, c))) {
                        long run = next - p;
                        if (base != NULL) {
                                memcpy(base, p, run);
                                base += run;
                        }
                        count += run;
                        previous = c;
                }

                p = next;
        }

        return count;
}

/* @overload squeeze(*sets)
 *
 * Replaces substrings of `self` of {#length} > 1 consisting of the same
 * character _c_ with _c_ itself, where _c_ is a member of the intersection of
 * the character sets in _sets_.
 *
 * If _sets_ is empty, then the set of all Unicode characters is used.
 *
 * The complement of all Unicode characters and a given set of characters may
 * be specified by prefixing a non-empty set with ‘`^`’ (U+005E CIRCUMFLEX
 * ACCENT).
 *
 * Any sequence of characters _a_-_b_ inside a set will expand to also
 * include all characters whose codepoints lay between those of _a_ and _b_.
 *
 * Any taint or untrust is inherited by the result.
 *
 * @param [Array<U::String, #to_str>] sets Set of characters to squeeze to intersect
 * @return [U::String] `self` with any substring of {#length} > 1 squeezed */
VALUE
rb_u_string_squeeze(int argc, VALUE *argv, VALUE self)
{
        const UString *string = RVAL2USTRING(self);

        if (USTRING_LENGTH(string) == 0)
                return Qnil;

        struct tr_table table;
        if (argc > 0)
                tr_table_initialize_from_strings(&table, argc, argv);

        struct tr_table *table_pointer = (argc > 0) ? &table : NULL;

        long count = rb_u_string_squeeze_loop(string, table_pointer, NULL);
        if (count == 0)
                return self;

        char *remaining = ALLOC_N(char, count + 1);
        rb_u_string_squeeze_loop(string, table_pointer, remaining);
        remaining[count] = '\0';

        return rb_u_string_new_own(remaining, count);
}
