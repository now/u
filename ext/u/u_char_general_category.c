#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "data/general-category.h"


/* {{{1
 * Determine the Unicode character type of ‘c’.
 */
enum u_general_category
u_char_general_category(uint32_t c)
{
        int16_t index;

	if (c <= UNICODE_LAST_CHAR_PART1)
                index = general_category_table_part1[c >> 8];
        else if (UNICODE_FIRST_CHAR_PART2 <= c && c <= UNICODE_LAST_CHAR)
                index = general_category_table_part2[(c - UNICODE_FIRST_CHAR_PART2) >> 8];
	else
		return U_GENERAL_CATEGORY_OTHER_NOT_ASSIGNED;

	if (index >= UNICODE_MAX_TABLE_INDEX)
		return index - UNICODE_MAX_TABLE_INDEX;

        return general_category_data[index][c & 0xff];
}
