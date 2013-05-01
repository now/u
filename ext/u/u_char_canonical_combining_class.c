#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "canonical_combining_class.h"


/* {{{1
 * Return the combining class of ‘c’.
 */
enum u_canonical_combining_class
u_char_canonical_combining_class(uint32_t c)
{
        return s_canonical_combining_class(c);
}
