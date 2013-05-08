#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "data/attributes.h"

#include "attributes.h"


/* This function may only be called if C has been verified to be of a
 * UnicodeType that supports attributes, as it doesn’t perform bounds checking
 * on C. */
uint32_t
_u_attribute(uint32_t c)
{
        uint32_t page = c >> 8;
        uint32_t index = page <= UNICODE_LAST_PAGE_PART1 ?
                attr_table_part1[page] :
                attr_table_part2[(c - UNICODE_FIRST_CHAR_PART2) >> 8];

        if (index == UNICODE_MAX_TABLE_INDEX)
                return 0;

        return attr_data[index][c & 0xff];
}

/* {{{1
 * Convert ‘c’ to its uppercase representation (if any).
 */
uint32_t
_u_special_case_table_lookup(uint32_t c)
{
        uint32_t tv = _u_attribute(c);

        if (tv >= UNICODE_SPECIAL_CASE_TABLE_START)
                u_decode_n(&tv,
                           special_case_table +
                           tv - UNICODE_SPECIAL_CASE_TABLE_START, 4);

        if (tv == '\0')
                return c;

        return tv;
}


/* {{{1
 * Output titlecases where appropriate.
 */
const char *
_u_special_case(uint32_t v, enum u_general_category category, bool upper)
{
	const char *p = special_case_table + v - UNICODE_SPECIAL_CASE_TABLE_START;
	if (category != U_GENERAL_CATEGORY_LETTER_TITLECASE)
		p = u_next(p);
        return upper ? p + u_n_bytes(p) + 1 : p;
}
