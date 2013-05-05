#include "extconf.h"
#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "u.h"

#ifdef HAVE_ICONV
#  include <iconv.h>
#  include <limits.h>
#endif

size_t
u_recode(char *result, size_t m, const char *string, size_t n,
         const char *codeset)
{
        iconv_t cd = iconv_open(codeset, "UTF-8");
        if (cd == (iconv_t)-1)
                return 0;

        bool done = false;
        bool failed = false;
        bool final = false;
        bool too_big = false;
        char *p = (char *)string;
        size_t p_left = n;
        // We need to align the buffer.
        union { unsigned int align; char buffer[4096]; } b;
        char *base = m > 0 ? result : b.buffer;
        char *q = base;
        size_t q_left = m > 0 ? m : sizeof(b.buffer);
        size_t written = 0;
        while (!done && !failed) {
                size_t err = final ?
                        iconv(cd, NULL, NULL, &q, &q_left) :
                        iconv(cd, &p, &p_left, &q, &q_left);
                if (err == (size_t)-1) {
                        switch (errno) {
                        case EINVAL:
                                done = true;
                                break;
                        case E2BIG:
                                written += q - base;
                                if (!too_big) {
                                        too_big = true;
                                        base = b.buffer;
                                }
                                q = base;
                                q_left = sizeof(b.buffer);
                                errno = 0;
                                break;
                        default:
                                failed = true;
                                break;
                        }
                } else {
                        if (!final)
                                final = true;
                        else
                                done = true;
                }
        }
        *q = '\0';

        int saved_errno = errno;
        if (iconv_close(cd) < 0 && failed)
                errno = saved_errno;

        return written + (q - base);
}
