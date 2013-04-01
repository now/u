#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "data/attributes.h"

#include "attributes.h"

const uint32_t (*_u_attr_data)[256] = attr_data;
const int16_t *_u_attr_table_part1 = attr_table_part1;
const int16_t *_u_attr_table_part2 = attr_table_part2;
const char *_u_special_case_table = special_case_table;

/* {{{1
 * Convert ‘c’ to its uppercase representation (if any).
 */
uint32_t
_u_special_case_table_lookup(uint32_t c)
{
        uint32_t tv = s_attribute(c);

        if (tv >= UNICODE_SPECIAL_CASE_TABLE_START)
                tv = u_aref_char(_u_special_case_table +
                                 tv - UNICODE_SPECIAL_CASE_TABLE_START);

        if (tv == '\0')
                return c;

        return tv;
}


/* {{{1
 * Output titlecases where appropriate.
 */
size_t
_u_special_case_output(char *buf, int offset, int type, bool upper)
{
	const char *p = _u_special_case_table + offset;

	if (type != U_LETTER_TITLECASE)
		p = u_next(p);

	if (upper)
		p += u_byte_length(p) + 1;

	size_t len = u_byte_length(p);

	if (buf != NULL)
		memcpy(buf, p, len);

	return len;
}
