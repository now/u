#include <ruby.h>
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "attributes.h"
#include "titled.h"
#include "types.h"

#include "locale_type.h"


#define COMBINING_DOT_ABOVE                     ((unichar)0x0307)
#define COMBINING_GREEK_YPOGEGRAMMENI           ((unichar)0x0345)
#define LATIN_CAPITAL_LETTER_I_WITH_DOT_ABOVE   ((unichar)0x0130)
#define GREEK_CAPITAL_LETTER_IOTA               ((unichar)0x0399)


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
                return _u_special_case_output(buf,
                                              tv - UNICODE_SPECIAL_CASE_TABLE_START,
                                              type, upper);

        if (type == UNICODE_TITLECASE_LETTER) {
                unichar tu = _u_titlecase_table_lookup(c, true);
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
	size_t len = 0;

	const char *p = str;
        const char *end = p + max;
	bool p_was_i = false;
        while (P_WITHIN_STR(p, end, use_max)) {
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
u_upcase_impl(const char *str, size_t max, bool use_max, size_t *new_length)
{
	assert(str != NULL);

	LocaleType locale_type = _u_locale_type();

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
u_upcase(const char *str)
{
	return u_upcase_impl(str, 0, false, NULL);
}


/* {{{1
 * Convert all characters in ‘str’ to their uppercase representation if
 * applicable.  Returns the freshly allocated representation.  Do this for at
 * most ‘len˚ bytes from ‘str’.
 */
char *
u_upcase_n(const char *str, size_t len, size_t *new_length)
{
	return u_upcase_impl(str, len, true, new_length);
}
