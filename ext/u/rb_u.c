#include <ruby.h>
#include <re.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>
#include "u.h"
#include "private.h"
#include "rb_private.h"
#include "rb_u_string.h"

void
need_at_least_n_arguments(int argc, int n)
{
        static const char *const words[] = {
                NULL,   NULL, "two",   "three", "four",
                "five", "six", "seven", "eight", "nine"
        };

        if (argc >= n)
                return;

        if (n == 1)
                rb_raise(rb_eArgError, "need at least one argument");
        else if (1 < n && n < 10)
                rb_raise(rb_eArgError, "need at least %s arguments", words[n]);
        else
                rb_raise(rb_eArgError, "need at least %d arguments", n);
}

void
need_m_to_n_arguments(int argc, int m, int n)
{
        if (argc < m || argc > n)
                rb_raise(rb_eArgError,
                         "wrong number of arguments (%d for %d..%d)", argc, m, n);
}

unichar
_rb_u_aref_char_validated(const char *str, const char *end)
{
        /* TODO: if str_end <= str, then throw another error
         *         rb_raise(rb_eArgError, "empty string");*/
        unichar c = u_aref_char_validated_n(str, end - str);
        switch (c) {
        case UTF_BAD_INPUT_UNICHAR:
                rb_raise(rb_eArgError, "input isn’t valid UTF-8");
        case UTF_INCOMPLETE_INPUT_UNICHAR:
                rb_raise(rb_eArgError,
                         "input contains an incomplete UTF-8-encoded character");
        default:
                return c;
        }
}

char *
rb_u_prev_validated(const char *begin, const char *p)
{
        char *prev = u_find_prev(begin, p);
        if (prev == NULL)
                rb_raise(rb_eArgError, "input isn’t valid UTF-8");
        return prev;
}

char *
rb_u_next_validated(const char *p, const char *end)
{
        char *next = (char *)u_next(p);
        if (next > end)
                rb_raise(rb_eArgError, "input isn’t valid UTF-8");
        return next;
}

VALUE
rb_u_pattern_argument(VALUE pattern, bool quote)
{
        VALUE string;

        switch (TYPE(pattern)) {
        case T_REGEXP:
                return pattern;
        case T_STRING:
                string = pattern;
                break;
        default:
                string = rb_check_string_type(pattern);
                if (NIL_P(string))
                        Check_Type(pattern, T_REGEXP);
        }

        return rb_reg_regcomp(quote ? rb_reg_quote(string) : string);
}

#ifndef HAVE_RB_REG_BACKREF_NUMBER
static int
rb_reg_backref_number(UNUSED(VALUE match), VALUE backref)
{
        return NUM2INT(backref);
}
#endif

VALUE
rb_u_pattern_match_reference(VALUE reference)
{
        VALUE match = rb_backref_get();
	return rb_reg_nth_match(rb_reg_backref_number(match, reference), match);
}

void Init_u(void);
void
Init_u(void)
{
        VALUE mU = rb_define_module("U");

        Init_u_string(mU);
}
