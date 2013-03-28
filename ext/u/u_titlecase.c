#include <ruby.h>
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "u.h"
#include "private.h"

#include "locale_type.h"

#define LATIN_CAPITAL_LETTER_I ((unichar)0x0049)
#define LATIN_CAPITAL_LETTER_J ((unichar)0x004a)
#define LATIN_SMALL_LETTER_I ((unichar)0x0069)
#define LATIN_SMALL_LETTER_J ((unichar)0x006a)

struct titlecase_closure {
        const char *string;
        const char *previous;
        LocaleType locale_type;
        size_t n;
        char *result;
};

static void
titlecase_step(const char *p, struct titlecase_closure *closure)
{
        const char *t = closure->previous;
        while (t < p && !unichar_iscased(u_aref_char(t)))
                t = u_next(t);
        if (closure->result != NULL)
                memcpy(closure->result + closure->n, closure->previous, t - closure->previous);
        closure->n += t - closure->previous;
        if (t == p)
                return;
        closure->n += _u_upcase_step(closure->string, &t, p, true,
                                     closure->locale_type, true,
                                     OFFSET_IF(closure->result, closure->n));
        if (t + 1 < p && closure->locale_type == LOCALE_DUTCH &&
            (*t == LATIN_CAPITAL_LETTER_I || *t == LATIN_SMALL_LETTER_I) &&
            (*(t + 1) == LATIN_CAPITAL_LETTER_J || *(t + 1) == LATIN_SMALL_LETTER_J)) {
                if (closure->result != NULL)
                        closure->result[closure->n] = LATIN_CAPITAL_LETTER_J;
                closure->n++;
                t++;
        }
        t = u_next(t);
        while (t < p) {
                closure->n += _u_downcase_step(closure->string, t, p, true,
                                               closure->locale_type,
                                               OFFSET_IF(closure->result,
                                                         closure->n));
                t = u_next(t);
        }
}

static void
titlecase_word_break(const char *p, struct titlecase_closure *closure)
{
        if (closure->previous < p)
                titlecase_step(p, closure);
        closure->previous = p;
}

static size_t
titlecase_loop(const char *string, size_t length, bool use_length,
               LocaleType locale_type, char *result)
{
        const char *end = string + (use_length ? length : strlen(string));
        struct titlecase_closure closure = { string, string, locale_type, 0, result };
        u_word_breaks(string, length, (UnicodeWordBreakFn)titlecase_word_break, &closure);
        if (closure.previous != end)
                titlecase_step(end, &closure);
        return closure.n;
}

static char *
u_titlecase_in_locale_impl(const char *string, size_t length, bool use_length,
                           const char *locale, size_t *new_length)
{
	assert(string != NULL);

	LocaleType locale_type = _u_locale_type_from_string(locale);

        size_t n = titlecase_loop(string, length, use_length, locale_type, NULL);
	char *result = ALLOC_N(char, n + 1);
	titlecase_loop(string, length, use_length, locale_type, result);
	result[n] = '\0';

        if (new_length != NULL)
                *new_length = n;

	return result;
}

char *
u_titlecase(const char *string)
{
	return u_titlecase_in_locale_impl(string, 0, false, NULL, NULL);
}

char *
u_titlecase_n(const char *string, size_t length, size_t *new_length)
{
	return u_titlecase_in_locale_impl(string, length, true, NULL, new_length);
}

char *
u_titlecase_in_locale(const char *string, const char *locale)
{
        return u_titlecase_in_locale_impl(string, 0, false, locale, NULL);
}

char *
u_titlecase_in_locale_n(const char *string, size_t length, const char *locale,
                        size_t *new_length)
{
        return u_titlecase_in_locale_impl(string, length, true, locale, new_length);
}
