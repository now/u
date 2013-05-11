/* -*- coding: utf-8 -*- */

#include "extconf.h"
#include <errno.h>
#include <ruby.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
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

struct guarded_alloc_closure {
        void *result;
        size_t n;
};

static VALUE
guarded_alloc(VALUE data)
{
        struct guarded_alloc_closure *closure = (struct guarded_alloc_closure *)data;
        closure->result = (void *)ALLOC_N(char, closure->n);
        return Qnil;
}

void *
_rb_u_guarded_alloc(size_t n, ...)
{
        struct guarded_alloc_closure closure = { NULL, n };
        int error;
        rb_protect(guarded_alloc, (VALUE)&closure, &error);
        if (error == 0)
                return closure.result;
        va_list args;
        va_start(args, n);
        void *previous;
        while ((previous = va_arg(args, void *)) != NULL)
                free(previous);
        va_end(args);
        rb_exc_raise(rb_errinfo());
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
        if (!u_valid(string, length, &end))
                rb_u_raise(rb_eArgError,
                           "invalid byte sequence at byte %ld",
                           end - string);
}

VALUE
_rb_u_character_test(VALUE self, bool (*test)(uint32_t))
{
        const struct rb_u_string *s = RVAL2USTRING(self);
        for (const char *p = USTRING_STR(s), *end = USTRING_END(s); p < end; )
                if (!test(u_decode(&p, p, end)))
                        return Qfalse;
        return Qtrue;
}

VALUE
_rb_u_string_test_locale(int argc, VALUE *argv, VALUE self,
                         size_t convert(char *, size_t, const char *, size_t,
                                        const char *))
{
        const char *locale = NULL;

        VALUE rblocale;
        if (rb_scan_args(argc, argv, "01", &rblocale) == 1)
                locale = StringValuePtr(rblocale);

        const struct rb_u_string *string = RVAL2USTRING(self);

        size_t nfd_n = u_normalize(NULL, 0,
                                   USTRING_STR(string), USTRING_LENGTH(string),
                                   U_NORMALIZATION_FORM_D);
        char *nfd = ALLOC_N(char, nfd_n + 1);
        nfd_n = u_normalize(nfd, nfd_n + 1,
                            USTRING_STR(string), USTRING_LENGTH(string),
                            U_NORMALIZATION_FORM_D);

        size_t converted_n = convert(NULL, 0, nfd, nfd_n, locale);
        char *converted = _rb_u_guarded_alloc(converted_n + 1, nfd, NULL);
        convert(converted, converted_n + 1, nfd, nfd_n, locale);

        VALUE result = converted_n == nfd_n &&
                memcmp(converted, nfd, nfd_n) == 0 ? Qtrue : Qfalse;

        free(converted);
        free(nfd);

        return result;
}

VALUE
_rb_u_string_convert(VALUE self,
                     size_t convert(char *, size_t, const char *, size_t))
{
        const struct rb_u_string *string = RVAL2USTRING(self);

        size_t n = convert(NULL, 0, USTRING_STR(string), USTRING_LENGTH(string));
        char *converted = ALLOC_N(char, n + 1);
        convert(converted, n + 1, USTRING_STR(string), USTRING_LENGTH(string));

        return rb_u_string_new_c_own(self, converted, n);
}

static size_t
try_convert(char *result, size_t m, const struct rb_u_string *string,
            size_t convert(char *, size_t, const char *, size_t,
                           const char *), const char *locale)
{
        errno = 0;
        size_t n = convert(result, m, USTRING_STR(string), USTRING_LENGTH(string),
                           locale);
        if (errno != 0) {
                free(result);
                rb_u_raise_errno(errno, "can’t apply conversion");
        }
        return n;
}

VALUE
_rb_u_string_convert_locale(int argc, VALUE *argv, VALUE self,
                            size_t convert(char *, size_t, const char *, size_t,
                                           const char *),
                            const char *lc_env)
{
        const char *locale = NULL;

        VALUE rblocale;
        if (rb_scan_args(argc, argv, "01", &rblocale) == 1)
                locale = StringValuePtr(rblocale);
        else if (lc_env != NULL) {
                const char * const env[] = { "LC_ALL", lc_env, "LANG", NULL };
                for (const char * const *p = env; *p != NULL; p++)
                        if ((locale = getenv(*p)) != NULL)
                                break;
        }

        const struct rb_u_string *string = RVAL2USTRING(self);

        size_t n = try_convert(NULL, 0, string, convert, locale);
        char *converted = ALLOC_N(char, n + 1);
        size_t m = try_convert(converted, n + 1, string, convert, locale);
        if (m < n) {
                char *t = REALLOC_N(converted, char, m + 1);
                if (t != NULL)
                        converted = t;
                n = m;
        }

        return rb_u_string_new_c_own(self, converted, n);
}

VALUE
_rb_u_string_property(VALUE self, const char *name, int unknown,
                      int property(uint32_t), VALUE tosym(int))
{
        const struct rb_u_string *string = RVAL2USTRING(self);
        const char *p = USTRING_STR(string);
        const char *end = USTRING_END(string);
        if (p == end)
                return tosym(unknown);
        int first = property(u_decode(&p, p, end));
        while (p < end) {
                int value = property(u_decode(&p, p, end));
                if (value != first)
                        rb_u_raise(rb_eArgError,
                                   "string consists of characters with different %s values: :%s+, :%s",
                                   name,
                                   rb_id2name(SYM2ID(tosym(first))),
                                   rb_id2name(SYM2ID(tosym(value))));
        }
        return tosym(first);
}

#define SYMBOL2MODE(symbol, mode, id) do { \
        static ID id_##symbol; \
        if (id_##symbol == 0) \
                id_##symbol = rb_intern(#symbol); \
        if (id == id_##symbol) \
                return mode; \
} while (0)

enum u_normalization_form
_rb_u_symbol_to_normalization_form(VALUE symbol)
{
        if (!SYMBOL_P(symbol)) {
                VALUE inspected = rb_inspect(symbol);

                rb_u_raise(rb_eTypeError,
                           "not a symbol: %s",
                           StringValuePtr(inspected));
        }

        ID id = SYM2ID(symbol);

        SYMBOL2MODE(nfd, U_NORMALIZATION_FORM_D, id);
        SYMBOL2MODE(nfc, U_NORMALIZATION_FORM_C, id);
        SYMBOL2MODE(nfkd, U_NORMALIZATION_FORM_KD, id);
        SYMBOL2MODE(nfkc, U_NORMALIZATION_FORM_KC, id);

        rb_u_raise(rb_eArgError,
                   "unknown normalization form: :%s",
                   rb_id2name(SYM2ID(symbol)));
}

U_EXTERN void Init_u(void);
void
Init_u(void)
{
        VALUE mU = rb_define_module("U");

        Init_u_buffer(mU);
        Init_u_string(mU);
}
