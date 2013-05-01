#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"


/* {{{1
 * Determine whether ‘c’ is a digit, such as 0, 1, or 2.
 */
bool
u_char_isdigit(uint32_t c)
{
	return u_char_general_category(c) == U_GENERAL_CATEGORY_NUMBER_DECIMAL;
}
