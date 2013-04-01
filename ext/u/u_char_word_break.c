#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "word-break.h"


enum u_word_break
u_char_word_break(uint32_t c)
{
	return s_word_break(c);
}
