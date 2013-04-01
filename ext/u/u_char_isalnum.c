#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "types.h"


/* {{{1
 * Determine whether ‘c’ is an alphanumeric, such as A, B, C, 0, 1, or 2.
 */
bool
u_char_isalnum(uint32_t c)
{
	int type = s_type(c);

	return s_isdigit(type) || s_isalpha(type);
}
