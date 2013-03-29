#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"
#include "data/constants.h"
#include "data/grapheme-break.h"
#include "grapheme-break.h"

const uint8_t (*_u_grapheme_break_property_data)[256] = grapheme_break_property_data;
const int16_t *_u_grapheme_break_property_table_part1 = grapheme_break_property_table_part1;
const int16_t *_u_grapheme_break_property_table_part2 = grapheme_break_property_table_part2;
