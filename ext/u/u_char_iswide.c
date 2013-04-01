#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "u.h"

#include "private.h"

#include "data/wide.h"

/* Returns true if C is typically rendered a double-width cell on a terminal. */
bool
u_char_iswide(uint32_t c)
{
        return bsearch(&c, wide, lengthof(wide), sizeof(wide[0]),
                       u_char_interval_compare) != NULL;
}
