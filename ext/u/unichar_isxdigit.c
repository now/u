#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "types.h"


#define UNICHAR_FULLWIDTH_A     0xff21
#define UNICHAR_FULLWIDTH_F     0xff26
#define UNICHAR_FULLWIDTH_a     0xff41
#define UNICHAR_FULLWIDTH_f     0xff46


/* {{{1
 * Determine whether ‘c’ is a hexadecimal digit, such as 0, 1, ..., 9, a, b,
 * ..., f, or A, B, ..., F.
 */
bool
unichar_isxdigit(unichar c)
{
	return ((c >= 'a' && c <= 'f') ||
		(c >= 'A' && c <= 'F') ||
                (c >= UNICHAR_FULLWIDTH_a && c <= UNICHAR_FULLWIDTH_f) ||
                (c >= UNICHAR_FULLWIDTH_A && c <= UNICHAR_FULLWIDTH_F) ||
                (s_type(c) == U_DECIMAL_NUMBER));
}
