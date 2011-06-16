#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "types.h"


/* {{{1
 * Determine whether ‘c’ is an alphabetic (i.e. a letter), such as A, B, or C.
 */
bool
unichar_isalpha(unichar c)
{
	return s_isalpha(s_type(c));
}
