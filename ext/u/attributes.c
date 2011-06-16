#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "data/attributes.h"

#include "attributes.h"

const unichar (*_u_attr_data)[256] = attr_data;
const int16_t *_u_attr_table_part1 = attr_table_part1;
const int16_t *_u_attr_table_part2 = attr_table_part2;
const char *_u_special_case_table = special_case_table;

/* {{{1
 * Convert ‘c’ to its uppercase representation (if any).
 */
unichar
_u_special_case_table_lookup(unichar c)
{
        unichar tv = s_attribute(c);

        if (tv >= UNICODE_SPECIAL_CASE_TABLE_START)
                tv = u_aref_char(_u_special_case_table +
                                 tv - UNICODE_SPECIAL_CASE_TABLE_START);

        if (tv == '\0')
                return c;

        return tv;
}
