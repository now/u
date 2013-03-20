#include "rb_includes.h"
#include "rb_u_string_internal_tr.h"

/* @overload count(set, *sets)
 *
 * Counts the number of characters in `self` that are included in the
 * intersection of _set_ and any additional _sets_ of characters.
 *
 * The complement of all Unicode characters and a given set of characters may
 * be specified by prefixing a non-empty set with ‘`^`’ (U+005E CIRCUMFLEX
 * ACCENT).
 *
 * Any sequence of characters _a_-_b_ inside a set will expand to also
 * include all characters whose codepoints lay between those of _a_ and _b_.
 *
 * @param [U::String, #to_str] set Set of characters to count
 * @param [Array<U::String, #to_str>] sets Additional sets to intersect with
 *   _set_
 * @return [Integer] Number of characters included in the set of characters to
 *   count */
VALUE
rb_u_string_count(int argc, VALUE *argv, VALUE self)
{
        const UString *string = RVAL2USTRING(self);

        need_at_least_n_arguments(argc, 1);

        if (USTRING_LENGTH(string) == 0)
                return INT2FIX(0);

        struct tr_table table;
        tr_table_initialize_from_strings(&table, argc, argv);

        long count = 0;
        const char *end = USTRING_END(string);
        for (char const *p = USTRING_STR(string); p < end; p = u_next(p))
                if (tr_table_lookup(&table, _rb_u_aref_char_validated(p, end)))
                        count++;

        return LONG2NUM(count);
}
