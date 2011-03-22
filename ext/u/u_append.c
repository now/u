#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "u.h"
#include "private.h"

/* {{{1
 * Append an UTF-8 string onto another.
 */
void
u_append(char *dest, const char *src)
{
	strcat(dest, src);
}


/* {{{1
 * Append at most ‘n’ Unicode character from an UTF-8 string onto another.
 */
void
u_append_n(char *dest, const char *src, size_t n)
{
	const char *p;

	for (p = src; n > 0 && *p != NUL; p = u_next(p), n--) {
		/* this loop intentionally left empty */;
	}

	strncat(dest, src, p - src);
	dest[p - src] = NUL;
}
