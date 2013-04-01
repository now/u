#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "general-category.h"


/* {{{1
 * Determine the Unicode character type of ‘c’.
 */
UnicodeGeneralCategory
u_char_general_category(uint32_t c)
{
	return s_general_category(c);
}
