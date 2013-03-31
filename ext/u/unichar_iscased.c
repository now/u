#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "u.h"

#include "private.h"

#include "data/constants.h"
#include "data/cased.h"

#include "types.h"

bool
unichar_iscased(unichar c)
{
        return IS(s_type(c),
                  OR(U_LETTER_TITLECASE,
                     OR(U_LETTER_UPPERCASE,
                        OR(U_LETTER_LOWERCASE, 0)))) ||
                bsearch(&c, cased, lengthof(cased), sizeof(cased[0]),
                        unichar_interval_compare) != NULL;
}
