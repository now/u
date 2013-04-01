#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "general-category.h"


/* {{{1
 * Determine whether ‘c’ is an alphanumeric, such as A, B, C, 0, 1, or 2.
 */
bool
u_char_isalnum(uint32_t c)
{
	enum u_general_category category = s_general_category(c);

	return s_isdigit(category) || s_isalpha(category);
}
