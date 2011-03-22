#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "u.h"
#include "private.h"

/* {{{1
 * Copy the contents of an UTF-8 string to another.
 */
void
u_copy(char *dest, const char *src)
{
	strcpy(dest, src);
}


/* {{{1
 * Copy at most n Unicode characters from an UTF-8 string to another.  The
 * destination string will be ‹NUL›-terminated properly.
 */
void
u_copy_n(char *dest, const char *src, size_t n)
{
	const char *p;

	for (p = src; n > 0 && *p != NUL; p = u_next(p), n--) {
		/* this loop intentionally left empty */;
	}

	strncpy(dest, src, p - src);
	dest[p - src] = NUL;
}
