#include <ruby.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "u.h"
#include "utf8.h"
#include "private.h"

/* {{{1
 * The real implementation of ucs4_to_utf8() and ucs4_to_utf8_n() below.
 */
static char *
u_ucs4_to_u_n_impl(uint32_t *str, size_t n, bool use_n,
                   size_t *items_read, size_t *items_written)
{
	size_t result_n = 0;
	char *result = NULL, *p;

	for (size_t i = 0; (!use_n || i < n) && str[i] != '\0'; i++) {
		if (str[i] >= 0x80000000) {
			if (items_read != NULL)
				*items_read = i;

                        char buf[U_CHAR_MAX_BYTE_LENGTH];
                        int length = u_char_to_u(str[i], buf);
			rb_raise(rb_eArgError,
                                 "UCS-4 input contains character outside of range for UTF-8 (%*.s))",
                                 length, buf);
		}

		result_n += _utf8_length(str[i]);
	}

	p = result = ALLOC_N(char, result_n + 1);
	size_t i;
	for (i = 0; p < result + result_n; i++)
		p += u_char_to_u(str[i], p);
	*p = '\0';

	if (items_written != NULL)
		*items_written = p - result;
	if (items_read != NULL)
		*items_read = i;

	return result;
}

/* {{{1
 * Turn an UTF-32 encoded string into an UTF-8 encoded one.  If non-‹NULL›,
 * store the number of characters read and bytes written in ‘items_read’ and
 * ‘items_written’ respectivelly.
 */
char *
u_ucs4_to_u(uint32_t *str, size_t *items_read, size_t *items_written)
{
	return u_ucs4_to_u_n_impl(str, 0, false, items_read, items_written);
}

/* {{{1
 * Turn an UTF-32 encoded string into an UTF-8 encoded one.  If non-‹NULL›,
 * store the number of characters read and bytes written in ‘items_read’ and
 * ‘items_written’ respectivelly.  Examine at most ‘len’ characters from ‘str’.
 */
char *
u_ucs4_to_u_n(uint32_t *str, size_t n, size_t *items_read, size_t *items_written)
{
	return u_ucs4_to_u_n_impl(str, n, true, items_read, items_written);
}
