#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "u.h"

#include "private.h"

#include "data/wide-cjk.h"

/* Returns true if C is typically rendered a double-width cell on a terminal
 * under legacy East Asian locales.
 *
 * See http://www.unicode.org/reports/tr11/ for more details. */
bool
u_char_iswide_cjk(uint32_t c)
{
        return u_char_iswide(c) ||
                bsearch(&c, wide, lengthof(wide), sizeof(wide[0]),
                        u_char_interval_compare) != NULL;
}
