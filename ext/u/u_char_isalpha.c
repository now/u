#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "general-category.h"


/* {{{1
 * Determine whether ‘c’ is an alphabetic (i.e. a letter), such as A, B, or C.
 */
bool
u_char_isalpha(uint32_t c)
{
	return s_isalpha(s_general_category(c));
}
