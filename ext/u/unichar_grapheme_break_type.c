#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "grapheme-break.h"


UnicodeGraphemeBreakType
unichar_grapheme_break_type(unichar c)
{
	return s_grapheme_break_type(c);
}
