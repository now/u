#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "u.h"


size_t
unichar_width(unichar c)
{
        return unichar_iswide(c) ? 2 : unichar_iszerowidth(c) ? 0 : 1;
}
