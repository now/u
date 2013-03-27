#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"
#include "data/constants.h"
#include "data/word-break.h"
#include "word-break.h"

const uint8_t (*_u_word_break_property_data)[256] = word_break_property_data;
const int16_t *_u_word_break_property_table_part1 = word_break_property_table_part1;
const int16_t *_u_word_break_property_table_part2 = word_break_property_table_part2;
