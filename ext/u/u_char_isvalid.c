#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "u.h"
#include "utf8.h"


/* {{{1
 * Check whether ‘c’ is a valid Unicode character.
 */
bool
u_char_isvalid(uint32_t c)
{
	return UNICODE_ISVALID(c);
}
