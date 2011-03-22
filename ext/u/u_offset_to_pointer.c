#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "u.h"
#include "private.h"

/* {{{1
 * Convert an integer offset to a pointer within ‘str’.
 *
 */
char *
u_offset_to_pointer(const char *str, long offset)
{
	const char *p = str;

        if (offset > 0) {
                while (offset-- > 0)
                        p = u_next(p);
        } else {
                while (offset != 0) {
                        const char *base = p;
                        p += offset;
                        while ((*p & 0xc0) == 0x80)
                                p--;

                        offset += u_pointer_to_offset(p, base);
                 }
        }

	return (char *)p;
}
