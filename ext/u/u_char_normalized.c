#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "u.h"

#include "data/constants.h"
#include "data/normalization-quick-check.h"

enum u_normalized
u_char_normalized(uint32_t c, enum u_normalization_form form)
{
        int16_t i;
	if (c <= UNICODE_LAST_CHAR_PART1)
                i = normalization_quick_check_table_part1[c >> 8];
        else if (UNICODE_FIRST_CHAR_PART2 <= c && c <= UNICODE_LAST_CHAR)
                i = normalization_quick_check_table_part2[(c - UNICODE_FIRST_CHAR_PART2) >> 8];
	else
		return U_NORMALIZED_YES;

        return (i >= UNICODE_MAX_TABLE_INDEX ?
		i - UNICODE_MAX_TABLE_INDEX :
                normalization_quick_check_data[i][c & 0xff]) & (((1 << 2) - 1) << (2 * form));
}
