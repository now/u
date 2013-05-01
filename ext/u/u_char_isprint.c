#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"


/* {{{1
 * Determine whether ‘c’ is printable, which works the same as
 * u_char_isgraph(), except that space characters are also printable.
 */
bool
u_char_isprint(uint32_t c)
{
        return !IS(u_char_general_category(c),
                   OR(U_GENERAL_CATEGORY_OTHER_CONTROL,
                      OR(U_GENERAL_CATEGORY_OTHER_FORMAT,
                         OR(U_GENERAL_CATEGORY_OTHER_NOT_ASSIGNED,
                            OR(U_GENERAL_CATEGORY_OTHER_SURROGATE, 0)))));
}
