#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "u.h"

/* {{{1
 * Determine whether ‘c’ is a new-line.
 */
#define UNICHAR_NEXT_LINE               ((unichar)0x0085)
#define UNICHAR_LINE_SEPARATOR          ((unichar)0x2028)
#define UNICHAR_PARAGRAPH_SEPARATOR     ((unichar)0x2029)

bool
unichar_isnewline(unichar c)
{
        switch (c) {
        case '\n': case '\f': case '\r': case UNICHAR_NEXT_LINE:
        case UNICHAR_LINE_SEPARATOR: case UNICHAR_PARAGRAPH_SEPARATOR:
                return true;
        default:
                return false;
        }
}
