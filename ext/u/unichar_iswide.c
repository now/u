#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "u.h"

#include "private.h"

#include "data/wide.h"

/* Returns true if C is typically rendered a double-width cell on a terminal. */
bool
unichar_iswide(unichar c)
{
        return bsearch(&c, wide, lengthof(wide), sizeof(wide[0]),
                       unichar_interval_compare) != NULL;
}
