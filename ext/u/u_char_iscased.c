#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "u.h"

#include "private.h"

#include "data/constants.h"
#include "data/cased.h"

#include "general-category.h"

bool
u_char_iscased(uint32_t c)
{
        return IS(s_general_category(c),
                  OR(U_GENERAL_CATEGORY_LETTER_TITLECASE,
                     OR(U_GENERAL_CATEGORY_LETTER_UPPERCASE,
                        OR(U_GENERAL_CATEGORY_LETTER_LOWERCASE, 0)))) ||
                bsearch(&c, cased, lengthof(cased), sizeof(cased[0]),
                        u_char_interval_compare) != NULL;
}
