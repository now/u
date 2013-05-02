#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "u.h"
#include "utf8.h"


/* {{{1
 * Turn an Unicode character (UTF-32) into an UTF-8 character sequence and
 * store it in ‘result’, returning the length of the stored sequence.
 */
int
u_char_to_u_n(uint32_t c, char *result, size_t n)
{
	size_t len = 0;
	int first;

	if (c < UNI_LEN1) {
		first = 0;
		len = 1;
	} else if (c < UNI_LEN2) {
		first = 0xc0;
		len = 2;
	} else if (c < UNI_LEN3) {
		first = 0xe0;
		len = 3;
	} else if (c < UNI_LEN4) {
		first = 0xf0;
		len = 4;
	} else if (c < UNI_LEN5) {
		first = 0xf8;
		len = 5;
	} else {
		first = 0xfc;
		len = 6;
	}

	if (result != NULL && len <= n) {
		for (size_t i = len - 1; i > 0; i--)
			c = PUT_X(c, result[i]);

		result[0] = c | first;
	}

	return (int)len;
}

int
u_char_to_u(uint32_t c, char *result)
{
        return u_char_to_u_n(c, result, 6);
}
