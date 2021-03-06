#include "rb_includes.h"
#include "rb_u_string_internal_tr.h"

/* @overload count(set, *sets)
 *
 *   Returns the number of characters in the receiver that are included in the
 *   intersection of SET and any additional SETS of characters.
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
 *   @return [Integer] */
VALUE
rb_u_string_count(int argc, VALUE *argv, VALUE self)
{
        const struct rb_u_string *string = RVAL2USTRING(self);

        need_at_least_n_arguments(argc, 1);

        if (USTRING_LENGTH(string) == 0)
                return INT2FIX(0);

        struct tr_table table;
        tr_table_initialize_from_strings(&table, argc, argv);

        long count = 0;
        for (const char *p = USTRING_STR(string), *end = USTRING_END(string); p < end; )
                if (tr_table_lookup(&table, u_decode(&p, p, end)))
                        count++;

        return LONG2NUM(count);
}
