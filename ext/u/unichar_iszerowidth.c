#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "types.h"


#define SOFT_HYPHEN ((unichar)0x00ad)
#define ZERO_WIDTH_SPACE ((unichar)0x200b)


bool
unichar_iszerowidth(unichar c)
{
        if (UNLIKELY(c == SOFT_HYPHEN))
                return false;

        if (UNLIKELY(IS(s_type(c),
                        OR(U_MARK_NON_SPACING,
                           OR(U_MARK_ENCLOSING,
                              OR(U_OTHER_FORMAT, 0))))))
                return true;

        if (UNLIKELY((0x1160 <= c && c < 0x1200) || c == ZERO_WIDTH_SPACE))
                return true;

        return false;
}
