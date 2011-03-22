#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "u.h"
#include "utf8.h"


/* {{{1
 * Check whether ‘c’ is a valid Unicode character.
 */
bool
unichar_isvalid(unichar c)
{
	return UNICODE_ISVALID(c);
}
