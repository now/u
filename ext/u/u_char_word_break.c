#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "data/word-break.h"


enum u_word_break
u_char_word_break(uint32_t c)
{
        int16_t index;

	if (c <= UNICODE_LAST_CHAR_PART1)
                index = word_break_property_table_part1[c >> 8];
        else if (UNICODE_FIRST_CHAR_PART2 <= c && c <= UNICODE_LAST_CHAR)
                index = word_break_property_table_part2[(c - UNICODE_FIRST_CHAR_PART2) >> 8];
	else
		return U_WORD_BREAK_OTHER;

	if (index >= UNICODE_MAX_TABLE_INDEX)
		return index - UNICODE_MAX_TABLE_INDEX;

        return word_break_property_data[index][c & 0xff];
}
