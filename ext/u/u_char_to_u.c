#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "u.h"


/* {{{1
 * Turn an Unicode character (UTF-32) into an UTF-8 character sequence and
 * store it in ‘result’, returning the length of the stored sequence.
 */
int
u_char_to_u_n(uint32_t c, char *result, size_t n)
{
        if (c < 0x80) {
                if (n > 0)
                        result[0] = c;
                return 1;
        }

        size_t m;
        if (c < 0x800)
                m = 2;
        else if (c < 0x10000) {
                if (0xd800 <= c && c < 0xe000)
                        return 0;
                m = 3;
        } else if (c < U_N_CODEPOINTS)
                m = 4;
        else
                return 0;

        if (result != NULL && n >= m) {
                switch (m) {
                case 4: result[3] = 0x80 | (c & 0x3f); c = c >> 6; c |= 0x10000;
                case 3: result[2] = 0x80 | (c & 0x3f); c = c >> 6; c |= 0x800;
                case 2: result[1] = 0x80 | (c & 0x3f); c = c >> 6; c |= 0xc0;
                        result[0] = c;
                }
        }
        return (int)m;
}

int
u_char_to_u(uint32_t c, char *result)
{
        return u_char_to_u_n(c, result, 4);
}
