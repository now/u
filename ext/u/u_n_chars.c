#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "u.h"
#include "private.h"

/* {{{1
 * Retrieve the number of UTF-8 encoded Unicode characters in ‘str’.
 */
size_t
u_n_chars(const char *str)
{
        assert(str != NULL);
        size_t n = 0;
        for (const char *p = str, *end = str + strlen(str); *p != '\0'; n++)
                u_decode(&p, p, end);
        return n;
}


/* {{{1
 * Retrieve the number of UTF-8 encoded Unicode characters in ‘str’, examining
 * ‘len’ bytes.
 */
size_t
u_n_chars_n(const char *str, size_t n)
{
        assert(str != NULL || n == 0);
        if (n == 0)
                return 0;
        size_t m = 0;
        const char *p = str;
        const char *end = str + n;
        while (p < end) {
                u_decode(&p, p, end);
                m++;
        }

        return m;
}
