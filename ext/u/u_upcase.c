#include <ruby.h>
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "attributes.h"
#include "general-category.h"
#include "titled.h"

#define LATIN_SMALL_LETTER_I ((uint32_t)0x0069)
#define LATIN_CAPITAL_LETTER_I_WITH_DOT_ABOVE ((uint32_t)0x0130)
#define COMBINING_DOT_ABOVE ((uint32_t)0x0307)
#define COMBINING_GREEK_YPOGEGRAMMENI ((uint32_t)0x0345)
#define GREEK_CAPITAL_LETTER_IOTA ((uint32_t)0x0399)

#define CANONICAL_COMBINING_CLASS_ABOVE 230
#define CANONICAL_COMBINING_CLASS_NOT_REORDERED 0


static size_t
output_marks(const char **p, const char *end, bool use_end, char *result)
{
	size_t length = 0;

        const char *q = u_next(*p);
        while (P_WITHIN_STR(q, end, use_end)) {
		uint32_t c = u_aref_char(q);

                if (!s_ismark(s_general_category(c)))
                        break;

                length += u_char_to_u(c, OFFSET_IF(result, length));

                q = u_next(q);
	}

        *p = u_prev(q);

	return length;
}

static inline bool
is_after_soft_dotted(const char *string, const char *p)
{
        if (p == string)
                return false;

        for (const char *q = u_prev(p); q > string; q = u_prev(q)) {
                uint32_t c = u_aref_char(q);

                if (u_char_issoftdotted(c))
                        return true;

		int c_class = u_char_combining_class(u_aref_char(p));
                if (c_class == CANONICAL_COMBINING_CLASS_ABOVE ||
                    c_class == CANONICAL_COMBINING_CLASS_NOT_REORDERED)
                        return false;
	}

        return u_char_issoftdotted(u_aref_char(string));
}

static inline size_t
upcase_simple(uint32_t c, enum u_general_category category, char *result, bool title)
{
	uint32_t tv = s_attribute(c);

	if (tv >= UNICODE_SPECIAL_CASE_TABLE_START)
                return _u_special_case_output(result,
                                              tv - UNICODE_SPECIAL_CASE_TABLE_START,
                                              category, title);

        if (category == U_GENERAL_CATEGORY_LETTER_TITLECASE) {
                uint32_t tu = _u_titlecase_table_lookup(c, true);
                if (tu != c)
                        return u_char_to_u(tu, result);
        }

        return u_char_to_u(tv != '\0' ? tv : c, result);
}

size_t
_u_upcase_step(const char *string, const char **p, const char *end, bool use_end,
               enum locale locale, bool title, char *result)
{
        uint32_t c = u_aref_char(*p);

        if (!title && c == COMBINING_GREEK_YPOGEGRAMMENI) {
                /* When COMBINING GREEK YPOGEGRAMMENI (U+0345) is uppercased or
                 * titlecased, the result will be incorrect unless it is moved
                 * to the end of any sequence of combining marks, as the
                 * uppercase version isn’t a combining mark, but a GREEK
                 * CAPITAL LETTER IOTA (U+0399). */
                size_t length = output_marks(p, end, use_end, result);
                return length + u_char_to_u(GREEK_CAPITAL_LETTER_IOTA,
                                            OFFSET_IF(result, length));
        }

        if (locale == LOCALE_LITHUANIAN &&
            c == COMBINING_DOT_ABOVE &&
            is_after_soft_dotted(string, *p))
                return 0;

        if (locale == LOCALE_TURKIC && c == LATIN_SMALL_LETTER_I)
                return u_char_to_u(LATIN_CAPITAL_LETTER_I_WITH_DOT_ABOVE, result);

        enum u_general_category category = s_general_category(c);
        if (IS(category, OR(U_GENERAL_CATEGORY_LETTER_LOWERCASE,
                            OR(U_GENERAL_CATEGORY_LETTER_TITLECASE, 0))))
                return upcase_simple(c, category, result,
                                     title || category != U_GENERAL_CATEGORY_LETTER_LOWERCASE);

        size_t length = u_next(*p) - *p;

        if (result != NULL)
                memcpy(result, *p, length);

        return length;
}

static size_t
upcase_loop(const char *string, size_t length, bool use_length,
            enum locale locale, char *result)
{
	size_t n = 0;

	const char *p = string;
        const char *end = p + length;
        while (P_WITHIN_STR(p, end, use_length)) {
                n += _u_upcase_step(string, &p, end, use_length, locale,
                                    false, OFFSET_IF(result, n));

                p = u_next(p);
	}

	return n;
}

static char *
u_upcase_in_locale_impl(const char *string, size_t length, bool use_length,
                        const char *locale, size_t *new_length)
{
	assert(string != NULL);

	enum locale elocale = _u_locale_from_string(locale);

	size_t n = upcase_loop(string, length, use_length, elocale, NULL);
	char *result = ALLOC_N(char, n + 1);
	upcase_loop(string, length, use_length, elocale, result);
	result[n] = '\0';

        if (new_length != NULL)
                *new_length = n;

	return result;
}

char *
u_upcase(const char *string)
{
	return u_upcase_in_locale_impl(string, 0, false, NULL, NULL);
}

char *
u_upcase_n(const char *string, size_t length, size_t *new_length)
{
	return u_upcase_in_locale_impl(string, length, true, NULL, new_length);
}

char *
u_upcase_in_locale(const char *string, const char *locale)
{
	return u_upcase_in_locale_impl(string, 0, false, locale, NULL);
}

char *
u_upcase_in_locale_n(const char *string, size_t length, const char *locale,
                     size_t *new_length)
{
	return u_upcase_in_locale_impl(string, length, true, locale, new_length);
}
