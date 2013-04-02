#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "u.h"


/* {{{1
 * Check whether ‘c’ is a valid Unicode character.
 */
bool
u_char_isvalid(uint32_t c)
{
	return ((c) < 0x110000 &&
                (((c) & 0xffffff800) != 0xd800) &&
                ((c) < 0xfdd0 || (c) > 0xfdef) &&
                ((c) & 0xfffe) != 0xfffe);
}
