/*
 * contents: UTF8.count module function.
 *
 * Copyright © 2006 Nikolai Weibull <now@bitwi.se>
 */

#include "rb_includes.h"
#include "rb_utf_internal_tr.h"

VALUE
rb_utf_count(int argc, VALUE *argv, VALUE str)
{
        StringValue(str);
        need_at_least_n_arguments(argc, 1);

        if (RSTRING(str)->len == 0)
                return INT2FIX(0);

        unsigned int table[TR_TABLE_SIZE];
        tr_setup_table_from_strings(table, argc, &argv[0]);

        long count = 0;
        char const *p_end = RSTRING(str)->ptr + RSTRING(str)->len;
        for (char const *p = RSTRING(str)->ptr; p < p_end; p = utf_next(p))
                if (tr_table_lookup(table, _utf_char_validated(p, p_end)))
                        count++;

        return LONG2NUM(count);
}
