#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "u.h"
#include "private.h"

/* {{{1
 * Return a pointer to the previous UTF-8 character sequence in ‘str’.
 */
char *
u_prev(const char *p)
{
	while (true)
		if (!U_IS_CONTINUE_BYTE(*--p))
			return (char *)p;
}


/* {{{1
 * Synchronize and go to the previous UTF-8 character sequence in ‘p’.  This
 * search will not go beyond ‘begin’.  ‹NULL› is returned if it couldn't be
 * found.
 */
char *
u_find_prev(const char *begin, const char *p)
{
        if (p <= begin)
                return NULL;
	for (p--; p >= begin; p--)
		if (!U_IS_CONTINUE_BYTE(*p))
			return (char *)p;
	return NULL;
}
