#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "u.h"


size_t
u_char_width(uint32_t c)
{
        return u_char_iswide(c) ? 2 : u_char_iszerowidth(c) ? 0 : 1;
}
