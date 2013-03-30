#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "u.h"

#include "private.h"

#include "data/constants.h"

#include "types.h"


#define APOSTROPHE                      ((unichar)0x0027)
#define SOFT_HYPHEN                     ((unichar)0x00ad)
#define RIGHT_SINGLE_QUOTATION_MARK     ((unichar)0x2019)


bool
unichar_iscaseignorable(unichar c)
{
        return c == APOSTROPHE ||
                c == SOFT_HYPHEN ||
                c == RIGHT_SINGLE_QUOTATION_MARK ||
                IS(s_type(c),
                   OR(U_NON_SPACING_MARK,
                      OR(U_ENCLOSING_MARK,
                         OR(U_FORMAT,
                            OR(U_MODIFIER_LETTER,
                               OR(U_MODIFIER_SYMBOL, 0)))))) ? true : false;
}
