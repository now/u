#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"


bool
u_char_isdefined(uint32_t c)
{
        return !IS(u_char_general_category(c),
                   OR(U_GENERAL_CATEGORY_OTHER_NOT_ASSIGNED,
                      OR(U_GENERAL_CATEGORY_OTHER_SURROGATE, 0)));
}
