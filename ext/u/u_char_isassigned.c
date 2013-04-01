#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "general-category.h"


/* {{{1
 * Determine whether code point ‘c’ has been assigned a code value.
 */
bool
u_char_isassigned(uint32_t c)
{
	return s_general_category(c) != U_GENERAL_CATEGORY_OTHER_NOT_ASSIGNED;
}
