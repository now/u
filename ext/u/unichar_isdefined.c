#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "types.h"


bool
unichar_isdefined(unichar c)
{
        return !IS(s_type(c),
                   OR(UNICODE_UNASSIGNED,
                      OR(UNICODE_SURROGATE, 0)));
}
