#include "rb_includes.h"
#include <re.h>

static VALUE
rb_u_string_substr(VALUE str, long offset, long len)
{
        if (len < 0)
                return Qnil;

        char *begin, *limit;
        if (!rb_u_string_begin_from_offset(str, offset, &begin, &limit))
                return Qnil;
        char *end = _utf_offset_to_pointer_failable(begin, len, limit);
        if (end == NULL)
                end = limit;

        VALUE substr = (begin == end) ?
                rb_u_string_new5(str, NULL, 0) :
                rb_u_string_new5(str, begin, end - begin);

        OBJ_INFECT(substr, str);

        return substr;
}

static VALUE
rb_u_string_substr_and_infect(VALUE str, long offset, long len, VALUE source)
{
        VALUE substr = rb_u_string_substr(str, offset, len);
        OBJ_INFECT(substr, source);
        return substr;
}

/* XXX: Stolen straight from string.c. */
static VALUE
rb_str_subpat(VALUE str, VALUE re, int nth)
{
        if (rb_reg_search(re, str, 0, 0) >= 0)
                return rb_reg_nth_match(nth, rb_backref_get());

        return Qnil;
}

static VALUE
rb_u_string_aref_num(VALUE str, long offset)
{
        char *begin, *limit;
        if (!rb_u_string_begin_from_offset(str, offset, &begin, &limit))
                return Qnil;

        char *end = rb_u_next_validated(begin, limit);

        return rb_u_string_new(begin, end - begin);
}

static VALUE
rb_u_string_aref_default(VALUE str, VALUE index)
{
        long n_chars = u_length_n(RSTRING(str)->ptr, RSTRING(str)->len);

        long begin, len;
        switch (rb_range_beg_len(index, &begin, &len, n_chars, 0)) {
        case Qfalse:
                return rb_u_string_aref_num(str, NUM2LONG(index));
        case Qnil:
                return Qnil;
        default:
                return rb_u_string_substr_and_infect(str, begin, len, index);
        }
}

static VALUE
rb_u_string_aref(VALUE str, VALUE index)
{
        switch (TYPE(index)) {
        case T_FIXNUM:
                return rb_u_string_aref_num(str, FIX2LONG(index));
        case T_REGEXP:
                return rb_str_subpat(str, index, 0);
        case T_STRING:
                if (rb_u_string_index(str, index, 0) != -1)
                        return rb_u_string_dup(index);
                return Qnil;
        default:
                return rb_u_string_aref_default(str, index);
        }
}

VALUE
rb_u_string_aref_m(int argc, VALUE *argv, VALUE str)
{
        StringValue(str);

        need_m_to_n_arguments(argc, 1, 2);

        if (argc == 1)
                return rb_u_string_aref(str, argv[0]);

        if (TYPE(argv[0]) == T_REGEXP)
                return rb_str_subpat(str, argv[0], NUM2INT(argv[1]));

        return rb_u_string_substr(str, NUM2INT(argv[0]), NUM2INT(argv[1]));
}
