#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "u.h"
#include "private.h"


/* {{{1
 * The real implementation of utf_width() and utf_width_n() below.
 */
static size_t
u_width_impl(const char *str, size_t len, bool use_len)
{
	assert(str != NULL);

	size_t width = 0;

	for (const char *p = str; (!use_len || p < str + len) && *p != '\0'; p = u_next(p))
		width += unichar_iswide(u_aref_char(p)) ? 2 : 1;

	return width;
}


/* {{{1
 * Calculate the width in cells of ‘str’.
 */
size_t
u_width(const char *str)
{
	return u_width_impl(str, 0, false);
}


/* {{{1
 * Calculate the width in cells of ‘str’, which is of length ‘len’.
 */
size_t
u_width_n(const char *str, size_t len)
{
	return u_width_impl(str, len, true);
}
