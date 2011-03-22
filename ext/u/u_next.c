#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "u.h"
#include "private.h"
#include "utf8.h"


/* {{{1
 * Synchronize and go to the next UTF-8 character sequence in ‘p’.  This search
 * will not go beyond ‘end’.  ‹NULL› is returned if it couldn't be found.
 */
char *
u_find_next(const char *p, const char *end)
{
	if (*p != NUL) {
		if (end != NULL) {
			for (p++; p < end && CONT_X(*p); p++) {
				/* this loop intentionally left empty */
			}
		} else {
			for (p++; CONT_X(*p); p++) {
				/* this loop intentionally left empty */
			}
		}
	}
	return (p == end) ? NULL : (char *)p;
}
