#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "types.h"


/* {{{1
 * Determine whether code point ‘c’ has been assigned a code value.
 */
bool
u_char_isassigned(uint32_t c)
{
	return s_type(c) != U_OTHER_NOT_ASSIGNED;
}
