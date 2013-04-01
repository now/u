#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "data/constants.h"
#include "data/line-break.h"
#include "private.h"

/* Figure out what break type the Unicode character ‘c’ possesses, if any.
 * This information is used for finding word and line boundaries, which is
 * useful when displaying Unicode text on screen. */
UnicodeLineBreak
u_char_line_break(uint32_t c)
{
        int16_t index;

	if (c <= UNICODE_LAST_CHAR_PART1)
                index = line_break_property_table_part1[c >> 8];
        else if (UNICODE_FIRST_CHAR_PART2 <= c && c <= UNICODE_LAST_CHAR)
                index = line_break_property_table_part2[(c - UNICODE_FIRST_CHAR_PART2) >> 8];
	else
		return U_LINE_BREAK_UNKNOWN;

	if (index >= UNICODE_MAX_TABLE_INDEX)
		return index - UNICODE_MAX_TABLE_INDEX;

        return line_break_property_data[index][c & 0xff];
}
