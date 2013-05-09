#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "u.h"

#include "data/bidi-mirroring.h"
#include "private.h"

uint32_t
u_char_mirror(uint32_t c)
{
        size_t i;
        return unicode_table_lookup(bidi_mirroring_table, c, &i) ?
                bidi_mirroring_table[i].mirrored_ch :
                c;
}
