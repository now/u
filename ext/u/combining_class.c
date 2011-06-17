#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "data/combining-class.h"
#include "combining_class.h"

const uint8_t (*_u_combining_class_data)[256] = combining_class_data;
const int16_t *_u_combining_class_table_part1 = combining_class_table_part1;
const int16_t *_u_combining_class_table_part2 = combining_class_table_part2;
