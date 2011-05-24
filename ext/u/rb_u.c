#include <ruby.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>
#include "u.h"
#include "private.h"
#include "rb_private.h"
#include "rb_u_buffer.h"
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

int
rb_unichar_to_u(unichar c, char *result)
{
        if (!unichar_isvalid(c))
                rb_raise(rb_eArgError, "not a Unicode character: %ld", c);

        return unichar_to_u(c, result);
}

void
rb_u_validate(const char *string, long length)
{
        const char *end;

        if (!utf_isvalid_n(string, length, &end))
                rb_raise(rb_eArgError, "invalid byte sequence at byte %ld", end - string);
}

void Init_u(void);
void
Init_u(void)
{
        VALUE mU = rb_define_module("U");

        Init_u_buffer(mU);
        Init_u_string(mU);
}
