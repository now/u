#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "u.h"

#include "private.h"

#include "data/constants.h"
#include "data/soft-dotted.h"

#include "general-category.h"

bool
u_char_issoftdotted(uint32_t c)
{
        return bsearch(&c, soft_dotted, lengthof(soft_dotted),
                       sizeof(soft_dotted[0]), u_char_interval_compare) != NULL;
}
