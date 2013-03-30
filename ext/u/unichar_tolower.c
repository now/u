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
unichar
unichar_tolower(unichar c)
{
	int type = s_type(c);

	if (type == U_UPPERCASE_LETTER)
                return _u_special_case_table_lookup(c);

        if (type == U_TITLECASE_LETTER)
                return _u_titlecase_table_lookup(c, false);

        return c;
}
