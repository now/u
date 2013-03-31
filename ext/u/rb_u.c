/* -*- coding: utf-8 -*- */

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
        if (argc < n)
                rb_u_raise(rb_eArgError,
                           "wrong number of arguments (%d for at least %d)",
                           argc, n);
}

void
need_m_to_n_arguments(int argc, int m, int n)
{
        if (argc < m || argc > n)
                rb_u_raise(rb_eArgError,
                           "wrong number of arguments (%d for %d..%d)",
                           argc, m, n);
}

unichar
_rb_u_aref_char_validated(const char *str, const char *end)
{
        if (str >= end)
                rb_u_raise(rb_eArgError, "String is empty");

        unichar c = u_aref_char_validated_n(str, end - str);
        switch (c) {
        case UTF_BAD_INPUT_UNICHAR:
                rb_u_raise(rb_eArgError, "input isn’t valid UTF-8");
        case UTF_INCOMPLETE_INPUT_UNICHAR:
                rb_u_raise(rb_eArgError,
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
                rb_u_raise(rb_eArgError, "input isn’t valid UTF-8");
        return prev;
}

char *
rb_u_next_validated(const char *p, const char *end)
{
        char *next = (char *)u_next(p);
        if (next > end)
                rb_u_raise(rb_eArgError, "input isn’t valid UTF-8");
        return next;
}

int
rb_unichar_to_u(unichar c, char *result)
{
        if (!unichar_isvalid(c))
                rb_u_raise(rb_eArgError, "not a Unicode character: %d", c);

        return unichar_to_u(c, result);
}

void
rb_u_validate(const char *string, long length)
{
        const char *end;

        if (!u_isvalid_n(string, length, &end))
                rb_u_raise(rb_eArgError,
                           "invalid byte sequence at byte %ld",
                           end - string);
}

VALUE
_rb_u_character_test(VALUE self, bool (*test)(unichar))
{
        const UString *string = RVAL2USTRING(self);

        const char *p = USTRING_STR(string);
        const char *end = USTRING_END(string);
        while (p < end) {
                if (!test(_rb_u_aref_char_validated(p, end)))
                        return Qfalse;

                p = u_next(p);
        }

        return Qtrue;
}

VALUE
_rb_u_string_test(VALUE self,
                  char *(convert)(const char *, size_t, size_t *))
{
        const UString *string = RVAL2USTRING(self);

        size_t nfd_length;
        char *nfd = u_normalize_n(USTRING_STR(string),
                                  USTRING_LENGTH(string),
                                  U_NORMALIZE_NFD,
                                  &nfd_length);

        size_t converted_length;
        char *converted = convert(nfd, nfd_length, &converted_length);

        VALUE result = converted_length == nfd_length &&
                memcmp(converted, nfd, nfd_length) == 0 ? Qtrue : Qfalse;

        free(converted);
        free(nfd);

        return result;
}

VALUE
_rb_u_string_test_in_locale(int argc, VALUE *argv, VALUE self,
                            char *(convert)(const char *, size_t,
                                            const char *, size_t *))
{
        const char *locale = NULL;

        VALUE rblocale;
        if (rb_scan_args(argc, argv, "01", &rblocale) == 1)
                locale = StringValuePtr(rblocale);

        const UString *string = RVAL2USTRING(self);

        size_t nfd_length;
        char *nfd = u_normalize_n(USTRING_STR(string),
                                  USTRING_LENGTH(string),
                                  U_NORMALIZE_NFD,
                                  &nfd_length);

        size_t converted_length;
        char *converted = convert(nfd,
                                  nfd_length,
                                  locale,
                                  &converted_length);

        VALUE result = converted_length == nfd_length &&
                memcmp(converted, nfd, nfd_length) == 0 ? Qtrue : Qfalse;

        free(converted);
        free(nfd);

        return result;
}

VALUE
_rb_u_string_case_in_locale(int argc, VALUE *argv, VALUE self,
                            char *(case_in_locale_n)(const char *, size_t,
                                                     const char *, size_t *))
{
        const char *locale = NULL;

        VALUE rblocale;
        if (rb_scan_args(argc, argv, "01", &rblocale) == 1)
                locale = StringValuePtr(rblocale);

        const UString *string = RVAL2USTRING(self);

        size_t length;
        char *cased = case_in_locale_n(USTRING_STR(string),
                                       USTRING_LENGTH(string),
                                       locale,
                                       &length);

        return rb_u_string_new_c_own(self, cased, length);
}

void Init_u(void);
void
Init_u(void)
{
        VALUE mU = rb_define_module("U");

        Init_u_buffer(mU);
        Init_u_string(mU);
}
