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
                   OR(UNICODE_CONTROL,
                      OR(UNICODE_FORMAT,
                         OR(UNICODE_UNASSIGNED,
                            OR(UNICODE_SURROGATE,
                               OR(UNICODE_SPACE_SEPARATOR, 0))))));
}
