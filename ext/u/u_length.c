#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "u.h"
#include "private.h"

/* {{{1
 * Retrieve the number of UTF-8 encoded Unicode characters in ‘str’.
 */
long
u_length(const char *str)
{
        assert(str != NULL);

        long n = 0;
        const char *p = str;
        while (*p != '\0') {
                n++;
                p = u_next(p);
        }

        return n;
}


/* {{{1
 * Retrieve the number of UTF-8 encoded Unicode characters in ‘str’, examining
 * ‘len’ bytes.
 */
long
u_length_n(const char *str, long len)
{
        assert(str != NULL || len == 0);

        if (len == 0)
                return 0;

        long n = 0;
        const char *p = str;
        const char *end = str + len;
        while (p < end) {
                n++;
                p = u_next(p);
        }

        /* This makes sure that we don’t count incomplete characters.  It won’t
         * save us from illegal UTF-8-sequences, however. */
        if (p > end)
                n--;

        return n;
}
