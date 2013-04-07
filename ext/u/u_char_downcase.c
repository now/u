#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "attributes.h"
#include "titled.h"
#include "general-category.h"


/* {{{1
 * Convert ‘c’ to its lowercase representation (if any).
 */
uint32_t
u_char_downcase(uint32_t c)
{
        switch (s_general_category(c)) {
        case U_GENERAL_CATEGORY_LETTER_UPPERCASE:
                return _u_special_case_table_lookup(c);
        case U_GENERAL_CATEGORY_LETTER_TITLECASE:
                return _u_titlecase_table_lookup(c, false);
        default:
                return c;
        }
}
