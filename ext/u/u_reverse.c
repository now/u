#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "u.h"
#include "private.h"


/* {{{1
 * The real implementation of utf_reverse() and utf_reverse_n() below.
 */
static char *
u_reverse_impl(const char *str, size_t len, bool use_len)
{
	if (!use_len)
		len = u_byte_length(str);

	char *result = malloc(sizeof(char) * (len + 1));
	char *r = result + len;
	const char *p = str;
        while (r > result) {
		uint8_t skip = s_u_skip_lengths[*(unsigned char *)p];
		r -= skip;
		for (char *m = r; skip > 0; skip--)
			*m++ = *p++;
	}
	result[len] = 0;

	return result;
}


/* {{{1
 * Return a new string which is ‘str’ reversed.
 */
char *
u_reverse(const char *str)
{
	return u_reverse_impl(str, 0, false);
}


/* {{{1
 * Return a new string which is ‘str’ reversed, examining at most ‘len’ bytes
 * of it.
 */
char *
u_reverse_n(const char *str, size_t len)
{
	return u_reverse_impl(str, len, true);
}
