#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"



/* {{{1
 * Determine whether ‘c’ is a control character, such as ‹NUL›.
 */
bool
u_char_iscntrl(uint32_t c)
{
	return u_char_general_category(c) == U_GENERAL_CATEGORY_OTHER_CONTROL;
}
