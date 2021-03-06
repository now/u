#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"


#define SOFT_HYPHEN ((uint32_t)0x00ad)
#define ZERO_WIDTH_SPACE ((uint32_t)0x200b)


bool
u_char_iszerowidth(uint32_t c)
{
        if (UNLIKELY(c == SOFT_HYPHEN))
                return false;

        if (UNLIKELY(IS(u_char_general_category(c),
                        OR(U_GENERAL_CATEGORY_MARK_NON_SPACING,
                           OR(U_GENERAL_CATEGORY_MARK_ENCLOSING,
                              OR(U_GENERAL_CATEGORY_OTHER_FORMAT, 0))))))
                return true;

        if (UNLIKELY((0x1160 <= c && c < 0x1200) || c == ZERO_WIDTH_SPACE))
                return true;

        return false;
}
