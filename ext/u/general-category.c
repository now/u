#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"
#include "data/constants.h"
#include "data/general-category.h"
#include "general-category.h"

const uint8_t (*_u_general_category_data)[256] = general_category_data;
const int16_t *_u_general_category_table_part1 = general_category_table_part1;
const int16_t *_u_general_category_table_part2 = general_category_table_part2;
