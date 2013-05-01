#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "data/canonical-combining-class.h"
#include "canonical_combining_class.h"

const uint8_t (*_u_canonical_combining_class_data)[256] = canonical_combining_class_data;
const int16_t *_u_canonical_combining_class_table_part1 = canonical_combining_class_table_part1;
const int16_t *_u_canonical_combining_class_table_part2 = canonical_combining_class_table_part2;
