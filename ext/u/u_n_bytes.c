#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "u.h"
#include "private.h"


/* {{{1
 * Retrieve the number of bytes making up the given UTF-8 string.
 */
size_t
u_n_bytes(const char *str)
{
	return strlen(str);
}
