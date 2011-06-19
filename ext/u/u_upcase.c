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


static size_t
output_marks(const char **p_inout, bool remove_dot, char *result)
{
	size_t length = 0;
	const char *p = *p_inout;

	for ( ; *p != '\0'; p = u_next(p)) {
		unichar c = u_aref_char(p);

                if (!s_ismark(s_type(c)))
                        break;

                if (!remove_dot || c != COMBINING_DOT_ABOVE)
                        length += unichar_to_u(c, OFFSET_IF(result, length));
	}

	*p_inout = p;

	return length;
}

static size_t
remove_all_combining_dot_above(unichar c, char *result)
{
        size_t decomp_length;
        unichar *decomp = unicode_canonical_decomposition(c, &decomp_length);

        size_t length = 0;
        for (size_t i = 0; i < decomp_length; i++)
                if (decomp[i] != COMBINING_DOT_ABOVE)
                        length += unichar_to_u(unichar_toupper(decomp[i]),
                                              OFFSET_IF(result, length));

        free(decomp);

        return length;
}

static size_t
upcase_lithuanian(const char **p, unichar c, int type, bool *was_i, char *result)
{
	if (c == 'i') {
		*was_i = true;
		return 0;
	}

	if (*was_i) {
                size_t length = remove_all_combining_dot_above(c, result);
		return length + output_marks(p, true, OFFSET_IF(result, length));
	}

	if (!s_ismark(type))
		*was_i = false;

	return 0;
}

static inline size_t
upcase_simple(unichar c, int type, char *result)
{
	bool upper = (type != UNICODE_LOWERCASE_LETTER);
	unichar tv = s_attribute(c);

	if (tv >= UNICODE_SPECIAL_CASE_TABLE_START)
                return _u_special_case_output(result,
                                              tv - UNICODE_SPECIAL_CASE_TABLE_START,
                                              type, upper);

        if (type == UNICODE_TITLECASE_LETTER) {
                unichar tu = _u_titlecase_table_lookup(c, true);
                if (tu != c)
                        return unichar_to_u(tu, result);
        }

        return unichar_to_u(tv != '\0' ? tv : c, result);
}

static size_t
upcase_step(const char **p, const char *prev, LocaleType locale_type,
            bool *was_i, char *result)
{
        unichar c = u_aref_char(prev);
        int type = s_type(c);

        if (locale_type == LOCALE_LITHUANIAN) {
                size_t length = upcase_lithuanian(p, c, type, was_i, result);
                if (length > 0)
                        return length;
        }

        if (locale_type == LOCALE_TURKIC && c == 'i')
                return unichar_to_u(LATIN_CAPITAL_LETTER_I_WITH_DOT_ABOVE, result);

        if (c == COMBINING_GREEK_YPOGEGRAMMENI) {
                /* Nasty, need to move it after other combining marks...this
                 * would go away if we normalized first. */
                /* TODO: don’t we need to make sure we don’t go beyond the end
                 * of ‘p’? */
                size_t length = output_marks(p, result, false);
                return length + unichar_to_u(GREEK_CAPITAL_LETTER_IOTA,
                                             OFFSET_IF(result, length));
        }

        if (IS(type, OR(UNICODE_LOWERCASE_LETTER,
                        OR(UNICODE_TITLECASE_LETTER, 0))))
                return upcase_simple(c, type, result);

        size_t length = u_skip_lengths[*(const unsigned char *)prev];

        if (result != NULL)
                memcpy(result, prev, length);

        return length;
}

static size_t
upcase_loop(const char *string, size_t length, bool use_length,
            LocaleType locale_type, char *result)
{
	size_t n = 0;

	const char *p = string;
        const char *end = p + length;
	bool p_was_i = false;
        while (P_WITHIN_STR(p, end, use_length)) {
		const char *prev = p;
		p = u_next(p);

                n += upcase_step(&p, prev, locale_type, &p_was_i,
                                 OFFSET_IF(result, n));
	}

	return n;
}

static char *
u_upcase_impl(const char *string, size_t length, bool use_length, size_t *new_length)
{
	assert(string != NULL);

	LocaleType locale_type = _u_locale_type();

	size_t n = upcase_loop(string, length, use_length, locale_type, NULL);
	char *result = ALLOC_N(char, n + 1);
	upcase_loop(string, length, use_length, locale_type, result);
	result[n] = '\0';

        if (new_length != NULL)
                *new_length = n;

	return result;
}

char *
u_upcase(const char *string)
{
	return u_upcase_impl(string, 0, false, NULL);
}

char *
u_upcase_n(const char *string, size_t length, size_t *new_length)
{
	return u_upcase_impl(string, length, true, new_length);
}
