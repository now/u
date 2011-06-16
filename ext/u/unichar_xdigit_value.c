#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "u.h"
#include "private.h"


#define UNICHAR_FULLWIDTH_A     0xff21
#define UNICHAR_FULLWIDTH_F     0xff26
#define UNICHAR_FULLWIDTH_a     0xff41
#define UNICHAR_FULLWIDTH_f     0xff46


/* {{{1
 * Return the numeric value of ‘c’ if it's a hexadecimal digit, or -1 if not.
 */
int
unichar_xdigit_value(unichar c)
{
	if (c >= 'a' && c <= 'f')
		return c - 'a' + 10;
	else if (c >= 'A' && c <= 'F')
		return c - 'A' + 10;
        else if (c >= UNICHAR_FULLWIDTH_a && c <= UNICHAR_FULLWIDTH_f)
                return c - UNICHAR_FULLWIDTH_a + 10;
        else if (c >= UNICHAR_FULLWIDTH_A && c <= UNICHAR_FULLWIDTH_F)
                return c - UNICHAR_FULLWIDTH_A + 10;
	else
		return unichar_digit_value(c);
}
