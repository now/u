#include "rb_includes.h"
#include "rb_u_re.h"

static VALUE
rb_u_string_scan_once(VALUE string, VALUE pattern, long *start, long *last)
{
        if (rb_reg_search(pattern, string, *start, false) < 0) {
                if (*last >= 0)
                        rb_reg_search(pattern, string, *last, false);

                return Qnil;
        }

        *last = *start;

        VALUE match = rb_backref_get();
        struct re_registers *registers = RMATCH_REGS(match);
        if (registers->beg[0] == registers->end[0]) {
                if (RSTRING_LEN(string) > registers->end[0])
                        *start = registers->end[0] +
                                (u_next(RSTRING_PTR(string) + registers->end[0]) -
                                 (RSTRING_PTR(string) + registers->end[0]));
                else
                        *start = registers->end[0] + 1;
        } else {
                *start = registers->end[0];
        }

        if (registers->num_regs == 1)
                return rb_u_string_new_rb(rb_reg_nth_match(0, match));

        VALUE result = rb_ary_new2(registers->num_regs);
        for (int i = 1; i < registers->num_regs; i++)
                rb_ary_push(result, rb_u_string_new_rb(rb_reg_nth_match(i, match)));

        return result;
}

static VALUE
rb_u_string_scan_block(VALUE self, VALUE string, VALUE pattern)
{
        VALUE result;
        long start = 0;
        long last = -1;

        while (!NIL_P(result = rb_u_string_scan_once(string, pattern, &start, &last)))
                rb_yield(result);

        return self;
}

static VALUE
rb_u_string_scan_array(VALUE string, VALUE pattern)
{
        VALUE result;
        long start = 0;
        long last = -1;

        VALUE array = rb_ary_new();
        while (!NIL_P(result = rb_u_string_scan_once(string, pattern, &start, &last)))
                rb_ary_push(array, result);

        return array;
}

VALUE
rb_u_string_scan(VALUE self, VALUE pattern)
{
        pattern = rb_u_pattern_argument(pattern, true);

        VALUE string = rb_str_to_str(self);

        if (rb_block_given_p())
                return rb_u_string_scan_block(self, string, pattern);

        return rb_u_string_scan_array(string, pattern);
}
