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
unichar_iswide_cjk(unichar c)
{
        return unichar_iswide(c) ||
                bsearch(&c, wide, lengthof(wide), sizeof(wide[0]),
                        unichar_interval_compare) != NULL;
}
