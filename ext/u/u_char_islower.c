#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"


/* {{{1
 * Determine whether ‘c’ is a lowercase letter, such as a, b, or c.
 */
bool
u_char_islower(uint32_t c)
{
	return u_char_general_category(c) == U_GENERAL_CATEGORY_LETTER_LOWERCASE;
}
