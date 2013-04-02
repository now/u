#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "u.h"
#include "private.h"


/* {{{1
 * Check if the given string begins with ‘prefix’.
 */
bool
u_has_prefix(const char *str, const char *prefix)
{
	assert(str != NULL);
	assert(prefix != NULL);

	do {
		if (*prefix == '\0')
			return true;
		else if (*str == '\0')
			return false;
	} while (*str++ == *prefix++);

	return false;
}
