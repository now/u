#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"


#define FULLWIDTH_A ((uint32_t)0xff21)
#define FULLWIDTH_F ((uint32_t)0xff26)
#define FULLWIDTH_a ((uint32_t)0xff41)
#define FULLWIDTH_f ((uint32_t)0xff46)


/* {{{1
 * Determine whether ‘c’ is a hexadecimal digit, such as 0, 1, ..., 9, a, b,
 * ..., f, or A, B, ..., F.
 */
bool
u_char_isxdigit(uint32_t c)
{
	return ((c >= 'a' && c <= 'f') ||
		(c >= 'A' && c <= 'F') ||
                (c >= FULLWIDTH_a && c <= FULLWIDTH_f) ||
                (c >= FULLWIDTH_A && c <= FULLWIDTH_F) ||
                (u_char_general_category(c) == U_GENERAL_CATEGORY_NUMBER_DECIMAL));
}
