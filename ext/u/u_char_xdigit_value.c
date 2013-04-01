#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "u.h"
#include "private.h"


#define FULLWIDTH_A ((uint32_t)0xff21)
#define FULLWIDTH_F ((uint32_t)0xff26)
#define FULLWIDTH_a ((uint32_t)0xff41)
#define FULLWIDTH_f ((uint32_t)0xff46)


/* {{{1
 * Return the numeric value of ‘c’ if it's a hexadecimal digit, or -1 if not.
 */
int
u_char_xdigit_value(uint32_t c)
{
	if (c >= 'a' && c <= 'f')
		return c - 'a' + 10;
	else if (c >= 'A' && c <= 'F')
		return c - 'A' + 10;
        else if (c >= FULLWIDTH_a && c <= FULLWIDTH_f)
                return c - FULLWIDTH_a + 10;
        else if (c >= FULLWIDTH_A && c <= FULLWIDTH_F)
                return c - FULLWIDTH_A + 10;
	else
		return u_char_digit_value(c);
}
