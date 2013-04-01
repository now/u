#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "general-category.h"


/* {{{1
 * Determine whether ‘c’ is an uppeercase letter, such as A, B, or C
 */
bool
u_char_isupper(uint32_t c)
{
	return s_general_category(c) == U_GENERAL_CATEGORY_LETTER_UPPERCASE;
}
