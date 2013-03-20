#include "rb_includes.h"
#include "rb_u_string_internal_tr.h"

static long
rb_u_string_delete_loop(const UString *string, struct tr_table *table,
                        char *result)
{
        long count = 0;

        const char *p = USTRING_STR(string);
        const char *end = USTRING_END(string);
        char *base = result;
        while (p < end) {
                unichar c = u_aref_char(p);
                const char *next = rb_u_next_validated(p, end);

                if (!tr_table_lookup(table, c)) {
                        long run = next - p;
                        if (base != NULL) {
                                memcpy(base, p, run);
                                base += run;
                        }
                        count += run;
                }

                p = next;
        }

        return count;
}

/* @overload delete(set, *sets)
 *
 * Removes characters in `self` that are included in the intersection of _set_
 * and any additional _sets_ of characters.
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
 * @param [U::String, #to_str] set Set of characters to delete
 * @param [Array<U::String, #to_str>] sets Additional sets to intersect with
 *   _set_
 * @return [U::String] `self` without any of the characters included in the set
 *   of characters to remove */
VALUE
rb_u_string_delete(int argc, VALUE *argv, VALUE self)
{
        const UString *string = RVAL2USTRING(self);

        need_at_least_n_arguments(argc, 1);

        if (USTRING_LENGTH(string) == 0)
                return self;

        struct tr_table table;
        tr_table_initialize_from_strings(&table, argc, argv);

        long count = rb_u_string_delete_loop(string, &table, NULL);
        if (count == 0)
                return self;

        char *remaining = ALLOC_N(char, count + 1);
        rb_u_string_delete_loop(string, &table, remaining);
        remaining[count] = '\0';

        VALUE result = rb_u_string_new_own(remaining, count);
        OBJ_INFECT(result, self);
        return result;
}
