#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "u.h"
#include "private.h"
#include "data/bidi-mirroring.h"


/* Store the mirrored representation of C in MIRRORED.
 *
 * Returns true if a mirrored representation was stored in MIRRORED. */
bool
u_char_mirror(uint32_t c, uint32_t *mirrored)
{
        size_t index;

        if (!unicode_table_lookup(bidi_mirroring_table, c, &index))
                return false;

        if (mirrored != NULL)
                *mirrored = bidi_mirroring_table[index].mirrored_ch;

        return true;
}
