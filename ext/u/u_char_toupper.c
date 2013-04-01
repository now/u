#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "attributes.h"
#include "titled.h"
#include "general-category.h"


uint32_t
u_char_toupper(uint32_t c)
{
	UnicodeGeneralCategory category = s_general_category(c);

	if (category == U_GENERAL_CATEGORY_LETTER_LOWERCASE)
                return _u_special_case_table_lookup(c);

        if (category == U_GENERAL_CATEGORY_LETTER_TITLECASE)
                return _u_titlecase_table_lookup(c, true);

        return c;
}
