#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "u.h"
#include "private.h"
#include "utf8.h"


/* {{{1
 * Return a pointer to the previous UTF-8 character sequence in ‘str’.
 */
char *
u_prev(const char *p)
{
	while (true) {
		p--;

		if (!CONT_X(*p))
			return (char *)p;
	}
}


/* {{{1
 * Synchronize and go to the previous UTF-8 character sequence in ‘p’.  This
 * search will not go beyond ‘begin’.  ‹NULL› is returned if it couldn't be
 * found.
 */
char *
u_find_prev(const char *begin, const char *p)
{
	for (p--; p >= begin; p--) {
		if (!CONT_X(*p))
			return (char *)p;
	}

	return NULL;
}
