#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "types.h"


/* {{{1
 * Determine the Unicode character type of ‘c’.
 */
UnicodeType
unichar_type(unichar c)
{
	return s_type(c);
}
