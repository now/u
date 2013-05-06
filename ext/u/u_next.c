#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "u.h"
#include "private.h"

/* {{{1
 * Synchronize and go to the next UTF-8 character sequence in ‘p’.  This search
 * will not go beyond ‘end’.  ‹NULL› is returned if it couldn't be found.
 */
char *
u_find_next(const char *p, const char *end)
{
        if (p >= end)
                return NULL;
	if (*p != '\0') {
		if (end != NULL)
			for (p++; p < end && U_IS_CONTINUE_BYTE(*p); p++)
                                ;
		else
			for (p++; U_IS_CONTINUE_BYTE(*p); p++)
                                ;
	}
	return (p == end) ? NULL : (char *)p;
}
