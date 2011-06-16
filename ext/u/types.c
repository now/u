#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"
#include "data/constants.h"
#include "data/types.h"
#include "types.h"

const char (*_u_type_data)[256] = type_data;
const int16_t *_u_type_table_part1 = type_table_part1;
const int16_t *_u_type_table_part2 = type_table_part2;
