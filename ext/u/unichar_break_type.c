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
        return SPLIT_UNICODE_TABLE_LOOKUP(break_property_data,
                                          break_property_table_part1,
                                          break_property_table_part2,
                                          c,
                                          UNICODE_BREAK_UNKNOWN);
}
