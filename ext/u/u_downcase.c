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


#define COMBINING_DOT_ABOVE                     ((unichar)0x0307)
#define LATIN_CAPITAL_LETTER_I                  ((unichar)0x0049)
#define LATIN_CAPITAL_LETTER_J                  ((unichar)0x004a)
#define LATIN_SMALL_LETTER_I                    ((unichar)0x0069)
#define LATIN_SMALL_LETTER_DOTLESS_I            ((unichar)0x0131)
#define LATIN_CAPITAL_LETTER_I_WITH_GRAVE       ((unichar)0x00cc)
#define LATIN_CAPITAL_LETTER_I_WITH_ACUTE       ((unichar)0x00cd)
#define LATIN_CAPITAL_LETTER_I_WITH_TILDE       ((unichar)0x0128)
#define LATIN_CAPITAL_LETTER_I_WITH_OGONEK      ((unichar)0x012e)
#define COMBINING_GRAVE_ACCENT                  ((unichar)0x0300)
#define COMBINING_ACUTE_ACCENT                  ((unichar)0x0301)
#define COMBINING_TILDE                         ((unichar)0x0303)
#define GREEK_CAPITAL_LETTER_SIGMA              ((unichar)0x03a3)
#define GREEK_SMALL_LETTER_SIGMA                ((unichar)0x03c3)
#define GREEK_SMALL_LETTER_FINAL_SIGMA          ((unichar)0x03c2)


#define CANONICAL_COMBINING_CLASS_ABOVE 230
#define CANONICAL_COMBINING_CLASS_NOT_REORDERED 0


static inline bool
has_more_above(const char *str, const char *end, bool use_end)
{
	for (const char *p = str; P_WITHIN_STR(p, end, use_end); p = u_next(p)) {
		int c_class = unichar_combining_class(u_aref_char(p));

		if (c_class == CANONICAL_COMBINING_CLASS_ABOVE)
			return true;

		if (c_class == CANONICAL_COMBINING_CLASS_NOT_REORDERED)
			return false;
	}

	return false;
}

static inline size_t
real_do_tolower(unichar c, int type, char *buf)
{
	unichar tv = s_attribute(c);

	if (tv >= UNICODE_SPECIAL_CASE_TABLE_START)
                return _u_special_case_output(buf,
                                              tv - UNICODE_SPECIAL_CASE_TABLE_START,
                                              type, false);

        if (type == UNICODE_TITLECASE_LETTER) {
                unichar tu = _u_titlecase_table_lookup(c, false);
                if (tu != c)
                        return unichar_to_u(tu, buf);
        }

        return unichar_to_u(tv != '\0' ? tv : c, buf);
}

static inline size_t
tolower_turkic_i(const char **p, const char *end, bool use_end, char *buf)
{
        unichar i = LATIN_SMALL_LETTER_DOTLESS_I;

        if (P_WITHIN_STR(*p, end, use_end) && u_aref_char(*p) == COMBINING_DOT_ABOVE) {
                *p = u_next(*p);
                i = LATIN_SMALL_LETTER_I;
        }

        return unichar_to_u(i, buf);
}

static size_t
tolower_lithuianian_i(unichar base, unichar combiner, char *buf)
{
        size_t len = unichar_to_u(base, buf);
        len += unichar_to_u(COMBINING_DOT_ABOVE, OFFSET_IF(buf, len));
        if (combiner != '\0')
                len += unichar_to_u(combiner, OFFSET_IF(buf, len));

        return len;
}

static inline bool
tolower_lithuanian(unichar c, const char **p, const char *end, bool use_end, char *buf, size_t *len)
{
        unichar base = LATIN_SMALL_LETTER_I;
        unichar combiner = '\0';

        switch (c) {
        case LATIN_CAPITAL_LETTER_I_WITH_GRAVE:
                combiner = COMBINING_GRAVE_ACCENT;
                break;
        case LATIN_CAPITAL_LETTER_I_WITH_ACUTE:
                combiner = COMBINING_ACUTE_ACCENT;
                break;
        case LATIN_CAPITAL_LETTER_I_WITH_TILDE:
                combiner = COMBINING_TILDE;
                break;
        case LATIN_CAPITAL_LETTER_I:
        case LATIN_CAPITAL_LETTER_J:
        case LATIN_CAPITAL_LETTER_I_WITH_OGONEK:
                if (!has_more_above(*p, end, use_end))
                        return false;

                base = unichar_tolower(c);
                break;
        default:
                return false;
        }

        *len = tolower_lithuianian_i(base, combiner, buf);
        return true;
}

static size_t
tolower_sigma(const char **p, const char *end, bool use_end, char *buf)
{
        unichar sigma = GREEK_SMALL_LETTER_FINAL_SIGMA;

        /* SIGMA maps differently depending on whether it is final or not.  The
         * following simplified test would fail in the case of combining marks
         * following the sigma, but I don't think that occurs in real text.
         * The test here matches that in ICU. */
        if ((!use_end || *p < end) && **p != '\0' && s_isalpha(s_type(u_aref_char(*p))))
                sigma = GREEK_SMALL_LETTER_SIGMA;

        return unichar_to_u(sigma, buf);
}

static inline size_t
real_tolower_one(const char **p, const char *prev, LocaleType locale_type,
                 const char *end, bool use_end, char *buf)
{
        unichar c = u_aref_char(prev);

        if (locale_type == LOCALE_TURKIC && c == LATIN_CAPITAL_LETTER_I)
                return tolower_turkic_i(p, end, use_end, buf);

        if (locale_type == LOCALE_LITHUANIAN) {
                size_t len;

                if (tolower_lithuanian(c, p, end, use_end, buf, &len))
                        return len;
        }

        if (c == GREEK_CAPITAL_LETTER_SIGMA)
                return tolower_sigma(p, end, use_end, buf);

        int type = s_type(c);
        if (IS(type, OR(UNICODE_UPPERCASE_LETTER,
                        OR(UNICODE_TITLECASE_LETTER, 0))))
                return real_do_tolower(c, type, buf);

        size_t len = u_skip_lengths[*(const unsigned char *)prev];

        if (buf != NULL)
                memcpy(buf, prev, len);

        return len;
}

static size_t
real_tolower(const char *str, size_t max, bool use_max, LocaleType locale_type,
             char *buf)
{
	size_t len = 0;

	const char *p = str;
        const char *end = str + max;
        while (P_WITHIN_STR(p, end, use_max)) {
		const char *prev = p;
		p = u_next(p);

                len += real_tolower_one(&p, prev, locale_type, end, use_max,
                                        OFFSET_IF(buf, len));
	}

	return len;
}

static char *
u_downcase_impl(const char *str, size_t max, bool use_max, size_t *new_length)
{
	assert(str != NULL);

	LocaleType locale_type = _u_locale_type();

	size_t len = real_tolower(str, max, use_max, locale_type, NULL);
	char *result = ALLOC_N(char, len + 1);
	real_tolower(str, max, use_max, locale_type, result);
	result[len] = '\0';

        if (new_length != NULL)
                *new_length = len;

	return result;
}

char *
u_downcase(const char *str)
{
	return u_downcase_impl(str, 0, false, NULL);
}

char *
u_downcase_n(const char *str, size_t len, size_t *new_length)
{
	return u_downcase_impl(str, len, true, new_length);
}
