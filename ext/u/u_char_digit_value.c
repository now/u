#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "attributes.h"
#include "general-category.h"

/* {{{1
 * Return the numeric value of ‘c’ if it's a decimal digit, or -1 if not.
 */
int
u_char_digit_value(uint32_t c)
{
	if (s_general_category(c) == U_GENERAL_CATEGORY_NUMBER_DECIMAL)
		return s_attribute(c);

        return -1;
}
