#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "general-category.h"


/* {{{1
 * Determine whether ‘c’ is a digit, such as 0, 1, or 2.
 */
bool
u_char_isdigit(uint32_t c)
{
	return s_general_category(c) == U_GENERAL_CATEGORY_NUMBER_DECIMAL;
}
