#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "u.h"

#include "private.h"

#include "data/constants.h"
#include "data/soft-dotted.h"

#include "types.h"

bool
unichar_issoftdotted(unichar c)
{
        return bsearch(&c, soft_dotted, lengthof(soft_dotted),
                       sizeof(soft_dotted[0]), unichar_interval_compare) != NULL;
}
