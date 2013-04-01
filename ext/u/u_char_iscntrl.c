#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "types.h"


/* {{{1
 * Determine whether ‘c’ is a control character, such as ‹NUL›.
 */
bool
u_char_iscntrl(uint32_t c)
{
	return s_type(c) == U_OTHER_CONTROL;
}
