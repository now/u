/*
 * contents: UTF8.aset module function.
 *
 * Copyright © 2006 Nikolai Weibull <now@bitwi.se>
 */

#include "rb_includes.h"
#include <re.h>

/* XXX: Stolen straight from string.c. */
#define BEG(no) regs->beg[no]
#define END(no) regs->end[no]

static VALUE
rb_str_subpat_set(VALUE str, VALUE re, int nth, VALUE val)
{
    VALUE match;
    long start, end, len;

    if (rb_reg_search(re, str, 0, 0) < 0) {
	rb_raise(rb_eIndexError, "regexp not matched");
    }
    match = rb_backref_get();
    if (nth >= RMATCH(match)->regs->num_regs) {
      out_of_range:
	rb_raise(rb_eIndexError, "index %d out of regexp", nth);
    }
    if (nth < 0) {
	if (-nth >= RMATCH(match)->regs->num_regs) {
	    goto out_of_range;
	}
	nth += RMATCH(match)->regs->num_regs;
    }

    start = RMATCH(match)->BEG(nth);
    if (start == -1) {
	rb_raise(rb_eIndexError, "regexp group %d not matched", nth);
    }
    end = RMATCH(match)->END(nth);
    len = end - start;
    rb_str_update(str, start, len, val);

    return val;
}

static VALUE
rb_u_aset_num(VALUE str, long offset, VALUE replacement)
{
        return rb_u_update(str, offset, 1, replacement);
}

static VALUE
rb_u_aset_default(VALUE str, VALUE index, VALUE replacement)
{
        long n_chars = utf_length_n(RSTRING(str)->ptr, RSTRING(str)->len);

        long begin, len;
        if (rb_range_beg_len(index, &begin, &len, n_chars, 2))
                return rb_u_update(str, begin, len, replacement);

        return rb_u_aset_num(str, NUM2LONG(index), replacement);
}

static VALUE
rb_u_aset(VALUE str, VALUE index, VALUE replacement)
{
        switch (TYPE(index)) {
        case T_FIXNUM:
                return rb_u_aset_num(str, FIX2LONG(index), replacement);
        case T_BIGNUM:
                return rb_u_aset_num(str, NUM2LONG(index), replacement);
        case T_REGEXP:
                return rb_str_subpat_set(str, index, 0, replacement);
        case T_STRING: {
                long begin = rb_u_index(str, index, 0);
                if (begin < 0)
                        rb_raise(rb_eIndexError, "string not matched");
                return rb_u_update(str,
                                     begin,
                                     utf_length_n(RSTRING(index)->ptr,
                                                  RSTRING(index)->len),
                                     replacement);
        }
        default:
                return rb_u_aset_default(str, index, replacement);
        }
}

VALUE
rb_u_aset_m(int argc, VALUE *argv, VALUE str)
{
        need_m_to_n_arguments(argc, 2, 3);

        StringValue(str);

        if (argc == 2)
                return rb_u_aset(str, argv[0], argv[1]);

        if (TYPE(argv[0]) == T_REGEXP)
                return rb_str_subpat_set(str, argv[0], NUM2INT(argv[1]), argv[2]);

        return rb_u_update(str, NUM2LONG(argv[0]), NUM2LONG(argv[1]), argv[2]);
}
