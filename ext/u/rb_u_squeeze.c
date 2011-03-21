/*
 * contents: UTF8.squeeze module function.
 *
 * Copyright © 2006 Nikolai Weibull <now@bitwi.se>
 */

#include "rb_includes.h"
#include "rb_u_internal_tr.h"

VALUE
rb_u_squeeze_bang(int argc, VALUE *argv, VALUE str)
{
        StringValue(str);
        if (RSTRING(str)->len == 0)
                return Qnil;

        unsigned int table[TR_TABLE_SIZE];
        if (argc == 0)
                for (int i = 0; i < TR_TABLE_SIZE; i++)
                        table[i] = ~0U;
        else
                tr_setup_table_from_strings(table, argc, &argv[0]);

        rb_str_modify(str);

        char *begin = RSTRING(str)->ptr;
        char const *end = begin + RSTRING(str)->len;

        /* We know that there is a character to eat (if the input isn’t
         * invalid), as we’ve already verified that RSTRING(str)->len > 0, so
         * ‘s_end’ must lay beyond ‘s’.  Also, as we validate when we fetch the
         * character, there’s no need to validate the call to utf_next(). */
        unichar previous = _utf_char_validated(begin, end);
        char *s = utf_next(begin);
        char *t = s;
        while (s < end) {
                unichar c = _utf_char_validated(s, end);
                char *next = utf_next(s);

                if (c != previous || !tr_table_lookup(table, c)) {
                        memmove(t, s, next - s);
                        t += next - s;
                        previous = c;
                }

                s = next;
        }
        *t = '\0';

        if (t - begin != RSTRING(str)->len) {
                RSTRING(str)->len = t - begin;
                return str;
        }

        return Qnil;
}

VALUE
rb_u_squeeze(int argc, VALUE *argv, VALUE str)
{
        StringValue(str);
        VALUE dup = rb_u_dup(str);
        rb_u_squeeze_bang(argc, argv, dup);
        return dup;
}
