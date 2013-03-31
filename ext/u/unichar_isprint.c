#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "types.h"


/* {{{1
 * Determine whether ‘c’ is printable, which works the same as
 * unichar_isgraph(), except that space characters are also printable.
 */
bool
unichar_isprint(unichar c)
{
        return !IS(s_type(c),
                   OR(U_OTHER_CONTROL,
                      OR(U_OTHER_FORMAT,
                         OR(U_OTHER_NOT_ASSIGNED,
                            OR(U_OTHER_SURROGATE, 0)))));
}
