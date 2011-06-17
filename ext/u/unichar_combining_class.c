#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "combining_class.h"


/* {{{1
 * Return the combinging class of ‘c’.
 */
int
unichar_combining_class(unichar c)
{
        return s_combining_class(c);
}
