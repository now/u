#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "attributes.h"
#include "titled.h"
#include "types.h"


/* {{{1
 * Convert ‘c’ to its lowercase representation (if any).
 */
uint32_t
u_char_tolower(uint32_t c)
{
	int type = s_type(c);

	if (type == U_LETTER_UPPERCASE)
                return _u_special_case_table_lookup(c);

        if (type == U_LETTER_TITLECASE)
                return _u_titlecase_table_lookup(c, false);

        return c;
}
