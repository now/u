#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "types.h"


bool
u_char_isdefined(uint32_t c)
{
        return !IS(s_type(c),
                   OR(U_OTHER_NOT_ASSIGNED,
                      OR(U_OTHER_SURROGATE, 0)));
}
