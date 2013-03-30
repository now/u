#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "types.h"


/* {{{1
 * Determine whether ‘c’ is a lowercase letter, such as a, b, or c.
 */
bool
unichar_islower(unichar c)
{
	return s_type(c) == U_LOWERCASE_LETTER;
}
