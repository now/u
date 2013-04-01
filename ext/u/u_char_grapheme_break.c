#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "grapheme-break.h"


enum u_grapheme_break
u_char_grapheme_break(uint32_t c)
{
	return s_grapheme_break(c);
}
