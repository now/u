#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "u.h"

/* {{{1
 * Determine whether ‘c’ is a new-line.
 */
#define NEXT_LINE ((uint32_t)0x0085)
#define LINE_SEPARATOR ((uint32_t)0x2028)
#define PARAGRAPH_SEPARATOR ((uint32_t)0x2029)

bool
u_char_isnewline(uint32_t c)
{
        switch (c) {
        case '\n': case '\f': case '\r': case NEXT_LINE:
        case LINE_SEPARATOR: case PARAGRAPH_SEPARATOR:
                return true;
        default:
                return false;
        }
}
