#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "data/canonical-combining-class.h"


/* {{{1
 * Return the combining class of ‘c’.
 */
enum u_canonical_combining_class
u_char_canonical_combining_class(uint32_t c)
{
        int16_t index;

	if (c <= UNICODE_LAST_CHAR_PART1)
                index = canonical_combining_class_table_part1[c >> 8];
        else if (UNICODE_FIRST_CHAR_PART2 <= c && c <= UNICODE_LAST_CHAR)
                index = canonical_combining_class_table_part2[(c - UNICODE_FIRST_CHAR_PART2) >> 8];
	else
		return 0;

	if (index >= UNICODE_MAX_TABLE_INDEX)
		return index - UNICODE_MAX_TABLE_INDEX;

        return canonical_combining_class_data[index][c & 0xff];
}
