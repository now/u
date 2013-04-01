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
u_char_combining_class(uint32_t c)
{
        return s_combining_class(c);
}
