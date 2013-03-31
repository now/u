#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "types.h"


/* {{{1
 * Determine whether ‘c’ is an uppeercase letter, such as A, B, or C
 */
bool
unichar_isupper(unichar c)
{
	return s_type(c) == U_LETTER_UPPERCASE;
}
