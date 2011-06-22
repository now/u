#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "data/constants.h"
#include "data/break.h"
#include "private.h"

/* Figure out what break type the Unicode character ‘c’ possesses, if any.
 * This information is used for finding word and line boundaries, which is
 * useful when displaying Unicode text on screen. */
UnicodeBreakType
unichar_break_type(unichar c)
{
        int16_t index;

	if (c <= UNICODE_LAST_CHAR_PART1)
                index = break_property_table_part1[c >> 8];
        else if (UNICODE_FIRST_CHAR_PART2 <= c && c <= UNICODE_LAST_CHAR)
                index = break_property_table_part2[(c - UNICODE_FIRST_CHAR_PART2) >> 8];
	else
		return UNICODE_BREAK_UNKNOWN;

	if (index >= UNICODE_MAX_TABLE_INDEX)
		return index - UNICODE_MAX_TABLE_INDEX;

        return break_property_data[index][c & 0xff];
}
