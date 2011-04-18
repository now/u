#include "rb_includes.h"
#include "rb_u_string_internal_tr.h"

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
