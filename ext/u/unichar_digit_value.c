#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "attributes.h"
#include "types.h"

/* {{{1
 * Return the numeric value of ‘c’ if it's a decimal digit, or -1 if not.
 */
int
unichar_digit_value(unichar c)
{
	if (s_type(c) == UNICODE_DECIMAL_NUMBER)
		return s_attribute(c);

        return -1;
}
