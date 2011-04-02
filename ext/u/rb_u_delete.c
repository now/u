#include "rb_includes.h"
#include "rb_u_internal_tr.h"

VALUE
rb_u_delete_bang(int argc, VALUE *argv, VALUE str)
{
        StringValue(str);
        need_at_least_n_arguments(argc, 1);

        if (RSTRING(str)->len == 0)
                return Qnil;

        unsigned int table[TR_TABLE_SIZE];
        tr_setup_table_from_strings(table, argc, &argv[0]);

        rb_str_modify(str);

        bool modified = false;
        char *s = RSTRING(str)->ptr;
        char const *s_end = s + RSTRING(str)->len;
        char *t = s;
        while (s < s_end) {
                unichar c = u_aref_char(s);

                char *next = rb_u_next_validated(s, s_end);
                if (tr_table_lookup(table, c)) {
                        modified = true;
                } else {
                        memmove(t, s, next - s);
                        t += next - s;
                }

                s = next;
        }
        *t = '\0';
        RSTRING(str)->len = t - RSTRING(str)->ptr;

        if (modified)
                return str;

        return Qnil;
}

VALUE
rb_u_delete(int argc, VALUE *argv, VALUE str)
{
        StringValue(str);
        need_at_least_n_arguments(argc, 1);

        VALUE dup = rb_u_dup(str);
        rb_u_delete_bang(argc, argv, dup);
        return dup;
}
