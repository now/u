#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "word-break.h"


UnicodeWordBreakType
unichar_word_break_type(unichar c)
{
	return s_word_break_type(c);
}
