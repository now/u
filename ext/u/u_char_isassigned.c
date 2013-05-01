#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"


/* {{{1
 * Determine whether code point ‘c’ has been assigned a code value.
 */
bool
u_char_isassigned(uint32_t c)
{
	return u_char_general_category(c) != U_GENERAL_CATEGORY_OTHER_NOT_ASSIGNED;
}
