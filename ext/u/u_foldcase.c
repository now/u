#include <ruby.h>
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "u.h"
#include "private.h"
#include "data/case-folding.h"


/* {{{1
 * The real implementation of case folding below.
 */

static bool
casefold_table_lookup(unichar c, char *folded, size_t *len)
{
        int index;

        if (!unicode_table_lookup(casefold_table, c, &index))
                return false;

        char const *folded_c = casefold_table[index].data;

        if (folded != NULL)
                strcpy(folded, folded_c);

        *len += u_byte_length(folded_c);

        return true;
}

static size_t
real_foldcase(const char *str, size_t max, bool use_max, char *buf)
{
	size_t len = 0;

        const char *p = str;
        const char *end = p + max;
        while (P_WITHIN_STR(p, end, use_max)) {
		unichar c = u_aref_char(p);
                p = u_next(p);

                if (casefold_table_lookup(c, OFFSET_IF(buf, len), &len))
                        continue;

		len += unichar_to_u(unichar_tolower(c), OFFSET_IF(buf, len));
	}

        return len;
}

static char *
u_foldcase_impl(const char *str, size_t max, bool use_max, size_t *new_length)
{
	assert(str != NULL);

	size_t len = real_foldcase(str, max, use_max, NULL);
        char *result = ALLOC_N(char, len + 1);
        result[0] = '\0';
        real_foldcase(str, max, use_max, result);
        result[len] = '\0';

        if (new_length != NULL)
                *new_length = len;

	return result;
}


/* {{{1
 * Convert a string into a form that is independent of case.  Return the
 * freshly allocated representation.
 */
char *
u_foldcase(const char *str)
{
	return u_foldcase_impl(str, 0, false, NULL);
}


/* {{{1
 * Convert a string into a form that is independent of case.  Return the
 * freshly allocated representation.  Do this for at most ‘len’ bytes from the
 * string.
 */
char *
u_foldcase_n(const char *str, size_t len, size_t *new_length)
{
	return u_foldcase_impl(str, len, true, new_length);
}
