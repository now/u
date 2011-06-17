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
has_more_above(const char *str)
{
	for (const char *p = str; *p != '\0'; p = u_next(p)) {
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

static size_t
tolower_turkic_i(const char **p, char *buf)
{
        unichar i = LATIN_SMALL_LETTER_DOTLESS_I;

        if (u_aref_char(*p) == COMBINING_DOT_ABOVE) {
                /* TODO: don’t we need to make sure we don’t go beyond the end
                 * of ‘p’? */
                *p = u_next(*p);
                i = LATIN_SMALL_LETTER_I;
        }

        return unichar_to_u(i, buf);
}

static size_t
tolower_lithuianian_i(char *buf, unichar base, unichar combiner)
{
        size_t len = unichar_to_u(base, buf);
        len += unichar_to_u(COMBINING_DOT_ABOVE, OFFSET_IF(buf, len));
        if (combiner != '\0')
                len += unichar_to_u(combiner, OFFSET_IF(buf, len));

        return len;
}

static size_t
tolower_sigma(const char **p, char *buf, const char *end, bool use_end)
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

static size_t
real_tolower_one(const char **p, const char *prev, char *buf,
                 LocaleType locale_type, const char *end, bool use_end)
{
        unichar c = u_aref_char(prev);
        int type = s_type(c);

        if (locale_type == LOCALE_TURKIC && c == 'I')
                return tolower_turkic_i(p, buf);

        /* Introduce an explicit dot above the lowercasing capital I’s
         * and J’s whenever there are more accents above.
         * [SpecialCasing.txt] */
        if (locale_type == LOCALE_LITHUANIAN) {
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
                case 'I':
                case 'J':
                case LATIN_CAPITAL_LETTER_I_WITH_OGONEK:
                        if (!has_more_above(*p))
                                goto no_lithuanian_i_casing;

                        base = unichar_tolower(c);
                        break;
                default:
                        goto no_lithuanian_i_casing;
                }

                return tolower_lithuianian_i(buf, base, combiner);
        }

no_lithuanian_i_casing:

        if (c == GREEK_CAPITAL_LETTER_SIGMA)
                return tolower_sigma(p, buf, end, use_end);

        if (IS(type, OR(UNICODE_UPPERCASE_LETTER,
                        OR(UNICODE_TITLECASE_LETTER, 0))))
                return real_do_tolower(c, type, buf);

        size_t len = u_skip_lengths[*(const unsigned char *)prev];

        if (buf != NULL)
                memcpy(buf, prev, len);

        return len;
}

static size_t
real_tolower(const char *str, size_t max, bool use_max, char *buf,
             LocaleType locale_type)
{
	size_t len = 0;

	const char *p = str;
        const char *end = str + max;
        while (P_WITHIN_STR(p, end, use_max)) {
		const char *prev = p;
		p = u_next(p);

                len += real_tolower_one(&p, prev, OFFSET_IF(buf, len),
                                        locale_type, end, use_max);
	}

	return len;
}

static char *
u_downcase_impl(const char *str, size_t max, bool use_max, size_t *new_length)
{
	assert(str != NULL);

	LocaleType locale_type = _u_locale_type();

	size_t len = real_tolower(str, max, use_max, NULL, locale_type);
	char *result = ALLOC_N(char, len + 1);
	real_tolower(str, max, use_max, result, locale_type);
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
