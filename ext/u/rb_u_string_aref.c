#include "rb_includes.h"
#include <re.h>

static VALUE
rb_u_string_substr_impl(VALUE self, long offset, long len, bool nil_on_empty)
{
        if (len < 0)
                return Qnil;

        const UString *string = RVAL2USTRING(self);

        const char *begin = rb_u_string_begin_from_offset(string, offset);
        if (begin == NULL)
                return Qnil;

        const char *end = u_offset_to_pointer_n(begin, len, USTRING_END(string) - begin);
        if (end == NULL)
                end = USTRING_END(string);

        if (nil_on_empty && begin == end)
                return Qnil;

        VALUE substr = rb_u_string_new(begin, end - begin);

        OBJ_INFECT(substr, self);

        return substr;
}

static VALUE
rb_u_string_substr(VALUE self, long offset, long len)
{
        return rb_u_string_substr_impl(self, offset, len, false);
}

static VALUE
rb_u_string_subpat(VALUE self, VALUE re, VALUE reference)
{
        if (rb_reg_search(re, StringValue(self), 0, 0) < 0)
                return Qnil;

        VALUE match = rb_u_pattern_match_reference(reference);

        /* TODO: If this pattern appears in the future, add
         * rb_u_string_new_rb_nilable. */
        return NIL_P(match) ? Qnil : rb_u_string_new_rb(match);
}

static VALUE
rb_u_string_aref_num(VALUE self, long offset)
{
        return rb_u_string_substr_impl(self, offset, 1, true);
}

static VALUE
rb_u_string_aref_default(VALUE self, VALUE index)
{
        const UString *string = RVAL2USTRING(self);
        long n_chars = u_length_n(USTRING_STR(string), USTRING_LENGTH(string));

        long begin, len;
        switch (rb_range_beg_len(index, &begin, &len, n_chars, 0)) {
        case Qfalse:
                return rb_u_string_aref_num(self, NUM2LONG(index));
        case Qnil:
                return Qnil;
        default:
                return rb_u_string_substr(self, begin, len);
        }
}

static VALUE
rb_u_string_aref(VALUE self, VALUE index)
{
        if (TYPE(index) == T_STRING || rb_obj_is_kind_of(index, rb_cUString)) {
                if (rb_u_string_index(self, index, 0) == -1)
                        return Qnil;

                return TYPE(index) == T_STRING ?
                        rb_u_string_new(RSTRING_PTR(index), RSTRING_LEN(index)) :
                        rb_u_string_dup(index);
        }

        switch (TYPE(index)) {
        case T_FIXNUM:
                return rb_u_string_aref_num(self, FIX2LONG(index));
        case T_REGEXP:
                return rb_u_string_subpat(self, index, INT2FIX(0));
        default:
                return rb_u_string_aref_default(self, index);
        }
}

VALUE
rb_u_string_aref_m(int argc, VALUE *argv, VALUE self)
{
        need_m_to_n_arguments(argc, 1, 2);

        if (argc == 1)
                return rb_u_string_aref(self, argv[0]);

        if (TYPE(argv[0]) == T_REGEXP)
                return rb_u_string_subpat(self, argv[0], argv[1]);

        return rb_u_string_substr(self, NUM2LONG(argv[0]), NUM2LONG(argv[1]));
}
