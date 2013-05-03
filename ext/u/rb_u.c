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

uint32_t
_rb_u_dref(const char *str, const char *end)
{
        if (str >= end)
                rb_u_raise(rb_eArgError, "string is empty");

        uint32_t c = u_dref_validated_n(str, end - str);
        switch (c) {
        case U_BAD_INPUT_CHAR:
                rb_u_raise(rb_eArgError, "input isn’t valid UTF-8");
        case U_INCOMPLETE_INPUT_CHAR:
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
rb_u_char_to_u(uint32_t c, char *result)
{
        if (!u_char_isvalid(c))
                rb_u_raise(rb_eArgError, "not a Unicode character: %#04x", c);

        return u_char_to_u(c, result);
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
_rb_u_character_test(VALUE self, bool (*test)(uint32_t))
{
        const struct rb_u_string *string = RVAL2USTRING(self);

        const char *p = USTRING_STR(string);
        const char *end = USTRING_END(string);
        while (p < end) {
                if (!test(_rb_u_dref(p, end)))
                        return Qfalse;

                p = u_next(p);
        }

        return Qtrue;
}

VALUE
_rb_u_string_test(VALUE self,
                  size_t convert(char *, size_t, const char *, size_t))
{
        const struct rb_u_string *string = RVAL2USTRING(self);

        rb_u_validate(USTRING_STR(string), USTRING_LENGTH(string));

        size_t nfd_n = u_normalize(NULL, 0,
                                   USTRING_STR(string), USTRING_LENGTH(string),
                                   U_NORMALIZE_NFD);
        char *nfd = ALLOC_N(char, nfd_n + 1);
        nfd_n = u_normalize(nfd, nfd_n + 1,
                            USTRING_STR(string), USTRING_LENGTH(string),
                            U_NORMALIZE_NFD);

        size_t converted_n = convert(NULL, 0, nfd, nfd_n);
        char *converted = ALLOC_N(char, converted_n + 1);
        convert(converted, converted_n + 1, nfd, nfd_n);

        VALUE result = converted_n == nfd_n &&
                memcmp(converted, nfd, nfd_n) == 0 ? Qtrue : Qfalse;

        free(converted);
        free(nfd);

        return result;
}

VALUE
_rb_u_string_test_new(int argc, VALUE *argv, VALUE self,
                      size_t convert(char *, size_t, const char *, size_t,
                                     const char *))
{
        const char *locale = NULL;

        VALUE rblocale;
        if (rb_scan_args(argc, argv, "01", &rblocale) == 1)
                locale = StringValuePtr(rblocale);

        const struct rb_u_string *string = RVAL2USTRING(self);

        rb_u_validate(USTRING_STR(string), USTRING_LENGTH(string));

        size_t nfd_n = u_normalize(NULL, 0,
                                   USTRING_STR(string), USTRING_LENGTH(string),
                                   U_NORMALIZE_NFD);
        char *nfd = ALLOC_N(char, nfd_n + 1);
        nfd_n = u_normalize(nfd, nfd_n + 1,
                            USTRING_STR(string), USTRING_LENGTH(string),
                            U_NORMALIZE_NFD);

        size_t converted_n = convert(NULL, 0, nfd, nfd_n, locale);
        char *converted = ALLOC_N(char, converted_n + 1);
        convert(converted, converted_n + 1, nfd, nfd_n, locale);

        VALUE result = converted_n == nfd_n &&
                memcmp(converted, nfd, nfd_n) == 0 ? Qtrue : Qfalse;

        free(converted);
        free(nfd);

        return result;
}

VALUE
_rb_u_string_case(int argc, VALUE *argv, VALUE self,
                  size_t string_case(char *, size_t, const char *, size_t,
                                     const char *))
{
        const char *locale = NULL;

        VALUE rblocale;
        if (rb_scan_args(argc, argv, "01", &rblocale) == 1)
                locale = StringValuePtr(rblocale);

        const struct rb_u_string *string = RVAL2USTRING(self);

        rb_u_validate(USTRING_STR(string), USTRING_LENGTH(string));

        size_t n = string_case(NULL, 0,
                               USTRING_STR(string), USTRING_LENGTH(string),
                               locale);
        char *cased = ALLOC_N(char, n + 1);
        string_case(cased, n + 1,
                    USTRING_STR(string), USTRING_LENGTH(string),
                    locale);

        return rb_u_string_new_c_own(self, cased, n);
}

VALUE
_rb_u_string_property(VALUE self, const char *name, int unknown,
                      int property(uint32_t), VALUE tosym(int))
{
        const struct rb_u_string *string = RVAL2USTRING(self);
        const char *p = USTRING_STR(string);
        const char *end = USTRING_END(string);
        if (p == end)
                return unknown;
        int first = property(u_dref_validated_n(p, end - p));
        p = u_next(p);
        while (p < end) {
                int value = property(u_dref_validated_n(p, end - p));
                if (value != first)
                        rb_u_raise(rb_eArgError,
                                   "string consists of characters with different %s values: :%s+, :%s",
                                   name,
                                   rb_id2name(SYM2ID(tosym(first))),
                                   rb_id2name(SYM2ID(tosym(value))));
                p = u_next(p);
        }
        return tosym(first);
}

U_EXTERN void Init_u(void);
void
Init_u(void)
{
        VALUE mU = rb_define_module("U");

        Init_u_buffer(mU);
        Init_u_string(mU);
}
