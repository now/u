#include <ruby.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "u.h"
#include "private.h"
#include "rb_private.h"
#include "rb_u_re.h"

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
