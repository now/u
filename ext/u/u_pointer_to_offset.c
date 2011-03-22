#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "u.h"
#include "private.h"


/* {{{1
 * Convert a pointer to an integer offset within ‘str’.
 */
long
u_pointer_to_offset(const char *str, const char *pos)
{
        if (pos < str)
                return -u_pointer_to_offset(pos, str);

	long offset = 0;
	for (const char *p = str; p < pos; p = u_next(p))
		offset++;

	return offset;
}
