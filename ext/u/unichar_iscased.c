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
                  OR(UNICODE_TITLECASE_LETTER,
                     OR(UNICODE_UPPERCASE_LETTER,
                        OR(UNICODE_LOWERCASE_LETTER, 0)))) ||
                bsearch(&c, cased, lengthof(cased), sizeof(cased[0]),
                       unichar_interval_compare) != NULL;
}
