#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "attributes.h"
#include "titled.h"
#include "types.h"


unichar
unichar_toupper(unichar c)
{
	int type = s_type(c);

	if (type == U_LETTER_LOWERCASE)
                return _u_special_case_table_lookup(c);

        if (type == U_LETTER_TITLECASE)
                return _u_titlecase_table_lookup(c, true);

        return c;
}
