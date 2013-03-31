#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "types.h"


/* {{{1
 * Determine whether ‘c’ is printable and not a space or control character such
 * as tab or <NUL›, such as A, B, or C.
 */
bool
unichar_isgraph(unichar c)
{
        return !IS(s_type(c),
                   OR(U_OTHER_CONTROL,
                      OR(U_OTHER_FORMAT,
                         OR(U_OTHER_NOT_ASSIGNED,
                            OR(U_OTHER_SURROGATE,
                               OR(U_SEPARATOR_SPACE, 0))))));
}
