#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"


/* {{{1
 * Determine whether ‘c’ is printable and not a space or control character such
 * as tab or <NUL›, such as A, B, or C.
 */
bool
u_char_isgraph(uint32_t c)
{
        return !IS(u_char_general_category(c),
                   OR(U_GENERAL_CATEGORY_OTHER_CONTROL,
                      OR(U_GENERAL_CATEGORY_OTHER_FORMAT,
                         OR(U_GENERAL_CATEGORY_OTHER_NOT_ASSIGNED,
                            OR(U_GENERAL_CATEGORY_OTHER_SURROGATE,
                               OR(U_GENERAL_CATEGORY_SEPARATOR_SPACE, 0))))));
}
