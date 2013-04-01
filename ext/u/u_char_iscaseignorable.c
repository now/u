#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "u.h"

#include "private.h"

#include "data/constants.h"

#include "general-category.h"


#define APOSTROPHE ((uint32_t)0x0027)
#define SOFT_HYPHEN ((uint32_t)0x00ad)
#define RIGHT_SINGLE_QUOTATION_MARK ((uint32_t)0x2019)


bool
u_char_iscaseignorable(uint32_t c)
{
        return c == APOSTROPHE ||
                c == SOFT_HYPHEN ||
                c == RIGHT_SINGLE_QUOTATION_MARK ||
                IS(s_general_category(c),
                   OR(U_GENERAL_CATEGORY_MARK_NON_SPACING,
                      OR(U_GENERAL_CATEGORY_MARK_ENCLOSING,
                         OR(U_GENERAL_CATEGORY_OTHER_FORMAT,
                            OR(U_GENERAL_CATEGORY_LETTER_MODIFIER,
                               OR(U_GENERAL_CATEGORY_SYMBOL_MODIFIER, 0)))))) ? true : false;
}
