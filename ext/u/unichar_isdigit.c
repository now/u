#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "types.h"


/* {{{1
 * Determine whether ‘c’ is a digit, such as 0, 1, or 2.
 */
bool
unichar_isdigit(unichar c)
{
	return s_type(c) == UNICODE_DECIMAL_NUMBER;
}