#include <ruby.h>
#include <assert.h>
#include <locale.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "u.h"
#include "private.h"
#include "data/constants.h"
#include "data/attributes.h"
#include "data/title-table.h"
#include "types.h"


#define COMBINING_DOT_ABOVE                     ((unichar)0x0307)
#define LATIN_CAPITAL_LETTER_I_WITH_DOT_ABOVE   ((unichar)0x0130)
#define COMBINING_GREEK_YPOGEGRAMMENI           ((unichar)0x0345)
#define GREEK_CAPITAL_LETTER_IOTA               ((unichar)0x0399)
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

/* {{{1
 * Determine whether ‘c’ is a titlecase letter, such as the slavic digraph Ǳ,
 * which at the beginning of a word is written as ǲ, where only the initial D
 * is capitalized.  (Complicated huh?)
 */
bool
unichar_istitle(unichar c)
{
	/* TODO: binary search helpful? */
	for (size_t i = 0; i < lengthof(title_table); i++)
		if (title_table[i][0] == c)
			return true;

	return false;
}


/* {{{1
 * Determine the Unicode character type of ‘c’.
 */
UnicodeType
unichar_type(unichar c)
{
	return s_type(c);
}


static inline unichar
s_attribute(unichar c)
{
        unichar page = c >> 8;
        unichar index = page <= UNICODE_LAST_PAGE_PART1 ?
                attr_table_part1[page] :
                attr_table_part2[page - 0xe00];

        if (index == UNICODE_MAX_TABLE_INDEX)
                return 0;

        return attr_data[index][c & 0xff];
}


/* {{{1
 * Convert ‘c’ to its uppercase representation (if any).
 */
static unichar
special_case_table_lookup(unichar c)
{
        unichar tv = s_attribute(c);

        if (tv >= UNICODE_SPECIAL_CASE_TABLE_START)
                tv = u_aref_char(special_case_table +
                                 tv - UNICODE_SPECIAL_CASE_TABLE_START);

        if (tv == '\0')
                return c;

        return tv;
}

static unichar
titlecase_table_lookup(unichar c, bool want_upper)
{
        for (size_t i = 0; i < lengthof(title_table); i++)
                if (title_table[i][0] == c)
                        return title_table[i][want_upper ? 1 : 2];

        return c;
}

unichar
unichar_toupper(unichar c)
{
	int type = s_type(c);

	if (type == UNICODE_LOWERCASE_LETTER)
                return special_case_table_lookup(c);
        
        if (type == UNICODE_TITLECASE_LETTER)
                return titlecase_table_lookup(c, true);

        return c;
}


/* {{{1
 * Convert ‘c’ to its lowercase representation (if any).
 */
unichar
unichar_tolower(unichar c)
{
	int type = s_type(c);

	if (type == UNICODE_UPPERCASE_LETTER)
                return special_case_table_lookup(c);
        
        if (type == UNICODE_TITLECASE_LETTER)
                return titlecase_table_lookup(c, false);

        return c;
}


/* {{{1
 * Convert ‘c’ to its titlecase representation (if any).
 */
unichar
unichar_totitle(unichar c)
{
	for (size_t i = 0; i < lengthof(title_table); i++)
		if (title_table[i][0] == c ||
                    title_table[i][1] == c ||
                    title_table[i][2] == c)
			return title_table[i][0];

        if (s_type(c) == UNICODE_LOWERCASE_LETTER)
                return unichar_toupper(c);

        return c;
}


/* {{{1
 * Return the numeric value of ‘c’ if it's a decimal digit, or -1 if not.
 */
int
unichar_digit_value(unichar c)
{
	if (s_type(c) == UNICODE_DECIMAL_NUMBER)
		return s_attribute(c);

        return -1;
}


/* {{{1
 * Return the numeric value of ‘c’ if it's a hexadecimal digit, or -1 if not.
 */
#define UNICHAR_FULLWIDTH_A     0xff21
#define UNICHAR_FULLWIDTH_F     0xff26
#define UNICHAR_FULLWIDTH_a     0xff41
#define UNICHAR_FULLWIDTH_f     0xff46
int
unichar_xdigit_value(unichar c)
{
	if (c >= 'a' && c <= 'f')
		return c - 'a' + 10;
	else if (c >= 'A' && c <= 'F')
		return c - 'A' + 10;
        else if (c >= UNICHAR_FULLWIDTH_a && c <= UNICHAR_FULLWIDTH_f)
                return c - UNICHAR_FULLWIDTH_a + 10;
        else if (c >= UNICHAR_FULLWIDTH_A && c <= UNICHAR_FULLWIDTH_F)
                return c - UNICHAR_FULLWIDTH_A + 10;
	else
		return unichar_digit_value(c);
}


/* {{{1
 * LocaleType: This ‹enum› is used for dealing with different locales for
 * turning strings into uppercase or lowercase.
 */
typedef enum {
	LOCALE_NORMAL,
	LOCALE_TURKIC,
	LOCALE_LITHUANIAN
} LocaleType;


/* {{{1
 * Retrieve the locale type from the environment (LC_CTYPE).
 */
static LocaleType
get_locale_type(void)
{
	const char *locale = setlocale(LC_CTYPE, NULL);

	if ((locale[0] == 'a' && locale[1] == 'z') ||
	    (locale[0] == 't' && locale[1] == 'r'))
		return LOCALE_TURKIC;

	if (locale[0] == 'l' && locale[1] == 't')
		return LOCALE_LITHUANIAN;

        return LOCALE_NORMAL;
}


/* {{{1
 * Put character marks found in ‘p_inout’ into itself.  If ‘remove_dot’ is
 * true, remove the dot over an uppercase I for a turkish locale.
 */
static size_t
output_marks(const char **p_inout, char *buf, bool remove_dot)
{
	size_t len = 0;
	const char *p = *p_inout;

	for ( ; *p != '\0'; p = u_next(p)) {
		unichar c = u_aref_char(p);

                if (!s_ismark(s_type(c)))
                        break;

                if (!remove_dot || c != COMBINING_DOT_ABOVE)
                        len += unichar_to_u(c, (buf != NULL) ? buf + len : NULL);
	}

	*p_inout = p;

	return len;
}

/* {{{1
 * Output titlecases where appropriate.
 */
static size_t
output_special_case(char *buf, int offset, int type, bool upper)
{
	const char *p = special_case_table + offset;

	if (type != UNICODE_TITLECASE_LETTER)
		p = u_next(p);

	if (upper)
		p += u_byte_length(p) + 1;

	size_t len = u_byte_length(p);

	if (buf != NULL)
		memcpy(buf, p, len);

	return len;
}

/* {{{1
 * Do uppercasing of ‘p’ for Lithuanian locales.
 */
static size_t
remove_all_combining_dot_above(unichar c, char *buf)
{
        size_t decomp_len;
        unichar *decomp = unicode_canonical_decomposition(c, &decomp_len);

        size_t len = 0;
        for (size_t i = 0; i < decomp_len; i++)
                if (decomp[i] != COMBINING_DOT_ABOVE)
                        len += unichar_to_u(unichar_toupper(decomp[i]),
                                              OFFSET_IF(buf, len));

        free(decomp);

        return len;
}

static size_t
real_toupper_lithuanian(const char **p, unichar c, int type, char *buf,
                        bool *was_i)
{
	if (c == 'i') {
		*was_i = true;
		return 0;
	}

	if (*was_i) {
                size_t len = remove_all_combining_dot_above(c, buf);
		return len + output_marks(p, OFFSET_IF(buf, len), true);
	}

	if (!s_ismark(type))
		*was_i = false;

	return 0;
}

/* {{{1
 * Do real upcasing. */
static inline size_t
real_do_toupper(unichar c, int type, char *buf)
{
	bool upper = (type != UNICODE_LOWERCASE_LETTER);
	unichar tv = s_attribute(c);

	if (tv >= UNICODE_SPECIAL_CASE_TABLE_START)
                return output_special_case(buf,
                                           tv - UNICODE_SPECIAL_CASE_TABLE_START,
                                           type, upper);

        if (type == UNICODE_TITLECASE_LETTER) {
                unichar tu = titlecase_table_lookup(c, true);
                if (tu != c)
                        return unichar_to_u(tu, buf);
        }

        return unichar_to_u(tv != '\0' ? tv : c, buf);
}

/* {{{1
 * Do real uppercasing of ‘str’.
 */
static size_t
real_toupper_one(const char **p, const char *prev, char *buf,
                 LocaleType locale_type, bool *was_i)
{
        unichar c = u_aref_char(prev);
        int type = s_type(c);

        if (locale_type == LOCALE_LITHUANIAN) {
                size_t len = real_toupper_lithuanian(p, c, type, buf, was_i);
                if (len > 0)
                        return len;
        }

        if (locale_type == LOCALE_TURKIC && c == 'i')
                return unichar_to_u(LATIN_CAPITAL_LETTER_I_WITH_DOT_ABOVE, buf);

        if (c == COMBINING_GREEK_YPOGEGRAMMENI) {
                /* Nasty, need to move it after other combining marks...this
                 * would go away if we normalized first. */
                /* TODO: don’t we need to make sure we don’t go beyond the end
                 * of ‘p’? */
                size_t len = output_marks(p, buf, false);
                return len + unichar_to_u(GREEK_CAPITAL_LETTER_IOTA,
                                          OFFSET_IF(buf, len));
        }
        
        if (IS(type, OR(UNICODE_LOWERCASE_LETTER,
                        OR(UNICODE_TITLECASE_LETTER, 0))))
                return real_do_toupper(c, type, buf);

        size_t len = u_skip_lengths[*(const unsigned char *)prev];

        if (buf != NULL)
                memcpy(buf, prev, len);

        return len;
}

static size_t
real_toupper(const char *str, size_t max, bool use_max, char *buf,
	     LocaleType locale_type)
{
	const char *p = str;
	size_t len = 0;
	bool p_was_i = false;

        while (P_WITHIN_STR(p, str, max, use_max)) {
		const char *prev = p;
		p = u_next(p);

                len += real_toupper_one(&p, prev, OFFSET_IF(buf, len),
                                        locale_type, &p_was_i);
	}

	return len;
}

/* {{{1
 * Wrapper around real_toupper() for dealing with memory allocation and such.
 */
static char *
utf_upcase_impl(const char *str, size_t max, bool use_max, size_t *new_length)
{
	assert(str != NULL);

	LocaleType locale_type = get_locale_type();

	size_t len = real_toupper(str, max, use_max, NULL, locale_type);
	char *result = ALLOC_N(char, len + 1);
	real_toupper(str, max, use_max, result, locale_type);
	result[len] = '\0';

        if (new_length != NULL)
                *new_length = len;

	return result;
}


/* {{{1
 * Convert all characters in ‘str’ to their uppercase representation if
 * applicable.  Returns the freshly allocated representation.
 */
char *
utf_upcase(const char *str)
{
	return utf_upcase_impl(str, 0, false, NULL);
}


/* {{{1
 * Convert all characters in ‘str’ to their uppercase representation if
 * applicable.  Returns the freshly allocated representation.  Do this for at
 * most ‘len˚ bytes from ‘str’.
 */
char *
utf_upcase_n(const char *str, size_t len, size_t *new_length)
{
	return utf_upcase_impl(str, len, true, new_length);
}


/* {{{1
 * Traverse the string checking for characters with combining class == 230
 * until a base character is found.
 */ 
static bool
has_more_above(const char *str)
{
	for (const char *p = str; *p != '\0'; p = u_next(p)) {
		int c_class = unichar_combining_class(u_aref_char(p));

		if (c_class == 230)
			return true;

		if (c_class == 0)
			return false;
	}

	return false;
}

static inline size_t
real_do_tolower(unichar c, int type, char *buf)
{
	unichar tv = s_attribute(c);

	if (tv >= UNICODE_SPECIAL_CASE_TABLE_START)
                return output_special_case(buf,
                                           tv - UNICODE_SPECIAL_CASE_TABLE_START,
                                           type, false);

        if (type == UNICODE_TITLECASE_LETTER) {
                unichar tu = titlecase_table_lookup(c, false);
                if (tu != c)
                        return unichar_to_u(tu, buf);
        }

        return unichar_to_u(tv != '\0' ? tv : c, buf);
}

/* {{{1
 * The real implementation of downcase.
 */
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
	const char *p = str;
        const char *end = str + max;
	size_t len = 0;

        while (P_WITHIN_STR(p, str, max, use_max)) {
		const char *prev = p;
		p = u_next(p);

                len += real_tolower_one(&p, prev, OFFSET_IF(buf, len),
                                        locale_type, end, use_max);
	}

	return len;
}


/* {{{1 */
static char *
u_downcase_impl(const char *str, size_t max, bool use_max, size_t *new_length)
{
	assert(str != NULL);

	LocaleType locale_type = get_locale_type();

	size_t len = real_tolower(str, max, use_max, NULL, locale_type);
	char *result = ALLOC_N(char, len + 1);
	real_tolower(str, max, use_max, result, locale_type);
	result[len] = '\0';

        if (new_length != NULL)
                *new_length = len;

	return result;
}


/* {{{1
 * Convert all characters in ‘str’ to their lowercase representation if
 * applicable.  Returns the freshly allocated representation.
 */
char *
u_downcase(const char *str)
{
	return u_downcase_impl(str, 0, false, NULL);
}


/* {{{1
 * Convert all characters in ‘str’ to their lowercase representation if
 * applicable.  Returns the freshly allocated representation.  Do this for at
 * most ‘len˚ bytes from ‘str’.
 */
char *
u_downcase_n(const char *str, size_t len, size_t *new_length)
{
	return u_downcase_impl(str, len, true, new_length);
}


/* }}}1 */
