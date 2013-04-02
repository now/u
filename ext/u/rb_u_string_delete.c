#include "rb_includes.h"
#include "rb_u_string_internal_tr.h"

static long
rb_u_string_delete_loop(const struct rb_u_string *string, struct tr_table *table,
                        char *result)
{
        long count = 0;

        const char *p = USTRING_STR(string);
        const char *end = USTRING_END(string);
        char *base = result;
        while (p < end) {
                uint32_t c = u_dref(p);
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
 *   Returns the receiver, minus any characters that are included in the
 *   intersection of SET and any additional SETS of characters, inheriting any
 *   taint and untrust.
 *
 *   The complement of all Unicode characters and a given set of characters may
 *   be specified by prefixing a non-empty set with ‘`^`’ (U+005E CIRCUMFLEX
 *   ACCENT).
 *
 *   Any sequence of characters _a_-_b_ inside a set will expand to also
 *   include all characters whose code points lay between those of _a_ and _b_.
 *
 *   @param [U::String, #to_str] set
 *   @param [Array<U::String, #to_str>] sets
 *   @return [U::String] */
VALUE
rb_u_string_delete(int argc, VALUE *argv, VALUE self)
{
        const struct rb_u_string *string = RVAL2USTRING(self);

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

        return rb_u_string_new_c_own(self, remaining, count);
}
