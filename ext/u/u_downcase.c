#include <ruby.h>
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "attributes.h"
#include "titled.h"
#include "types.h"

#include "locale_type.h"


#define LATIN_CAPITAL_LETTER_I ((uint32_t)0x0049)
#define LATIN_CAPITAL_LETTER_J ((uint32_t)0x004a)
#define LATIN_SMALL_LETTER_I ((uint32_t)0x0069)
#define LATIN_CAPITAL_LETTER_I_WITH_GRAVE ((uint32_t)0x00cc)
#define LATIN_CAPITAL_LETTER_I_WITH_ACUTE ((uint32_t)0x00cd)
#define LATIN_CAPITAL_LETTER_I_WITH_TILDE ((uint32_t)0x0128)
#define LATIN_CAPITAL_LETTER_I_WITH_OGONEK ((uint32_t)0x012e)
#define LATIN_CAPITAL_LETTER_I_WITH_DOT_ABOVE ((uint32_t)0x0130)
#define LATIN_SMALL_LETTER_DOTLESS_I ((uint32_t)0x0131)
#define COMBINING_GRAVE_ACCENT ((uint32_t)0x0300)
#define COMBINING_ACUTE_ACCENT ((uint32_t)0x0301)
#define COMBINING_TILDE ((uint32_t)0x0303)
#define COMBINING_DOT_ABOVE ((uint32_t)0x0307)
#define GREEK_CAPITAL_LETTER_SIGMA ((uint32_t)0x03a3)
#define GREEK_SMALL_LETTER_FINAL_SIGMA ((uint32_t)0x03c2)
#define GREEK_SMALL_LETTER_SIGMA ((uint32_t)0x03c3)

#define CANONICAL_COMBINING_CLASS_ABOVE 230
#define CANONICAL_COMBINING_CLASS_NOT_REORDERED 0


static inline bool
is_final_sigma(const char *string, const char *p, const char *end, bool use_end)
{
        if (p == string)
                return false;

        for (const char *q = u_next(p); P_WITHIN_STR(q, end, use_end); q = u_next(q)) {
                uint32_t c = u_aref_char(q);

                if (u_char_iscaseignorable(c))
                        continue;

                if (u_char_iscased(c))
                        return false;

                break;
        }

        for (const char *r = u_prev(p); r > string; r = u_prev(r)) {
                uint32_t c = u_aref_char(r);

                if (u_char_iscaseignorable(c))
                        continue;

                if (u_char_iscased(c))
                        return true;

                return false;
        }

        return u_char_iscased(u_aref_char(string));
}

static inline size_t
downcase_sigma(const char *string, const char *p, const char *end, bool use_end, char *result)
{
        return u_char_to_u(is_final_sigma(string, p, end, use_end) ?
                                GREEK_SMALL_LETTER_FINAL_SIGMA :
                                GREEK_SMALL_LETTER_SIGMA,
                            result);
}

static inline bool
has_more_above(const char *string, const char *end, bool use_end)
{
	for (const char *p = u_next(string); P_WITHIN_STR(p, end, use_end); p = u_next(p)) {
		int c_class = u_char_combining_class(u_aref_char(p));

		if (c_class == CANONICAL_COMBINING_CLASS_ABOVE)
			return true;

		if (c_class == CANONICAL_COMBINING_CLASS_NOT_REORDERED)
			return false;
	}

	return false;
}

static size_t
downcase_lithuianian_i(uint32_t base, uint32_t combiner, char *result)
{
        size_t length = u_char_to_u(base, result);
        length += u_char_to_u(COMBINING_DOT_ABOVE, OFFSET_IF(result, length));
        if (combiner != '\0')
                length += u_char_to_u(combiner, OFFSET_IF(result, length));

        return length;
}

static inline bool
downcase_lithuanian(uint32_t c, const char *p, const char *end, bool use_end, char *result, size_t *length)
{
        uint32_t base = LATIN_SMALL_LETTER_I;
        uint32_t combiner = '\0';

        switch (c) {
        case LATIN_CAPITAL_LETTER_I:
        case LATIN_CAPITAL_LETTER_J:
        case LATIN_CAPITAL_LETTER_I_WITH_OGONEK:
                if (!has_more_above(p, end, use_end))
                        return false;

                base = u_char_tolower(c);
                break;
        case LATIN_CAPITAL_LETTER_I_WITH_GRAVE:
                combiner = COMBINING_GRAVE_ACCENT;
                break;
        case LATIN_CAPITAL_LETTER_I_WITH_ACUTE:
                combiner = COMBINING_ACUTE_ACCENT;
                break;
        case LATIN_CAPITAL_LETTER_I_WITH_TILDE:
                combiner = COMBINING_TILDE;
                break;
        default:
                return false;
        }

        *length = downcase_lithuianian_i(base, combiner, result);
        return true;
}

static inline bool
is_before_dot(const char *p, const char *end, bool use_end)
{
	for (const char *q = u_next(p); P_WITHIN_STR(q, end, use_end); q = u_next(q)) {
                uint32_t c = u_aref_char(q);

                if (c == COMBINING_DOT_ABOVE)
                        return true;

		int c_class = u_char_combining_class(u_aref_char(p));
                if (c_class == CANONICAL_COMBINING_CLASS_ABOVE ||
                    c_class == CANONICAL_COMBINING_CLASS_NOT_REORDERED)
                        return false;
	}

        return false;
}

static inline size_t
downcase_turkic_i(const char *p, const char *end, bool use_end, char *result)
{
        return u_char_to_u(is_before_dot(p, end, use_end) ?
                                LATIN_SMALL_LETTER_I :
                                LATIN_SMALL_LETTER_DOTLESS_I,
                           result);
}

static inline bool
is_after_i(const char *string, const char *p)
{
        if (p == string)
                return false;

        for (const char *q = u_prev(p); q > string; q = u_prev(q)) {
                uint32_t c = u_aref_char(q);

                if (c == LATIN_CAPITAL_LETTER_I)
                        return true;

		int c_class = u_char_combining_class(u_aref_char(p));
                if (c_class == CANONICAL_COMBINING_CLASS_ABOVE ||
                    c_class == CANONICAL_COMBINING_CLASS_NOT_REORDERED)
                        return false;
	}

        return u_aref_char(string) == LATIN_CAPITAL_LETTER_I;
}

static inline size_t
downcase_turkic_dot_above(const char *string, const char *p, char *result)
{
        if (is_after_i(string, p))
                return 0;

        /* TODO: Try to use the memcpy() below here instead. */
        return u_char_to_u(COMBINING_DOT_ABOVE, result);
}

static inline size_t
downcase_simple(uint32_t c, int type, char *result)
{
	uint32_t tv = s_attribute(c);

	if (tv >= UNICODE_SPECIAL_CASE_TABLE_START)
                return _u_special_case_output(result,
                                              tv - UNICODE_SPECIAL_CASE_TABLE_START,
                                              type, false);

        if (type == U_LETTER_TITLECASE) {
                uint32_t tu = _u_titlecase_table_lookup(c, false);
                if (tu != c)
                        return u_char_to_u(tu, result);
        }

        return u_char_to_u(tv != '\0' ? tv : c, result);
}

size_t
_u_downcase_step(const char *string, const char *p, const char *end, bool use_end,
                 LocaleType locale_type, char *result)
{
        uint32_t c = u_aref_char(p);

        if (c == GREEK_CAPITAL_LETTER_SIGMA)
                return downcase_sigma(string, p, end, use_end, result);

        if (locale_type == LOCALE_LITHUANIAN) {
                size_t length;

                if (downcase_lithuanian(c, p, end, use_end, result, &length))
                        return length;
        }

        if (locale_type == LOCALE_TURKIC) {
                switch (c) {
                case LATIN_CAPITAL_LETTER_I:
                        return downcase_turkic_i(p, end, use_end, result);
                case LATIN_CAPITAL_LETTER_I_WITH_DOT_ABOVE:
                        c = LATIN_CAPITAL_LETTER_I;
                        break;
                case COMBINING_DOT_ABOVE:
                        return downcase_turkic_dot_above(string, p, result);
                default:
                        break;
                }
        }

        int type = s_type(c);
        if (IS(type, OR(U_LETTER_UPPERCASE, OR(U_LETTER_TITLECASE, 0))))
                return downcase_simple(c, type, result);

        size_t length = u_next(p) - p;

        if (result != NULL)
                memcpy(result, p, length);

        return length;
}

static size_t
downcase_loop(const char *string, size_t length, bool use_length,
              LocaleType locale_type, char *result)
{
	size_t n = 0;

	const char *p = string;
        const char *end = string + length;
        while (P_WITHIN_STR(p, end, use_length)) {
                n += _u_downcase_step(string, p, end, use_length, locale_type,
                                      OFFSET_IF(result, n));

                p = u_next(p);
	}

	return n;
}

static char *
u_downcase_in_locale_impl(const char *string, size_t length, bool use_length,
                          const char *locale, size_t *new_length)
{
	assert(string != NULL);

	LocaleType locale_type = _u_locale_type_from_string(locale);

	size_t n = downcase_loop(string, length, use_length, locale_type, NULL);
	char *result = ALLOC_N(char, n + 1);
	downcase_loop(string, length, use_length, locale_type, result);
	result[n] = '\0';

        if (new_length != NULL)
                *new_length = n;

	return result;
}

char *
u_downcase(const char *string)
{
	return u_downcase_in_locale_impl(string, 0, false, NULL, NULL);
}

char *
u_downcase_n(const char *string, size_t length, size_t *new_length)
{
	return u_downcase_in_locale_impl(string, length, true, NULL, new_length);
}

char *
u_downcase_in_locale(const char *string, const char *locale)
{
        return u_downcase_in_locale_impl(string, 0, false, locale, NULL);
}

char *
u_downcase_in_locale_n(const char *string, size_t length, const char *locale,
                       size_t *new_length)
{
        return u_downcase_in_locale_impl(string, length, true, locale, new_length);
}
