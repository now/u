#include "extconf.h"
#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "u.h"
#include "private.h"

static int
compare(const char *a, size_t a_n, const char *b, size_t b_n)
{
        int r = memcmp(a, b, a_n < b_n ? a_n : b_n);
        if (r == 0) {
                if (a_n < b_n)
                        return -1;
                else if (a_n > b_n)
                        return 1;
        }
        return r;
}

static size_t
ckey(char **result, char *buf, size_t m,
     const char *string, size_t n,
     const char *locale)
{
        errno = 0;
        size_t key_n = u_collation_key(buf, m, string, n, locale);
        if (errno != 0)
                return 0;
        if (key_n < m) {
                *result = buf;
                return key_n;
        }
        char *key = malloc(key_n + 1);
        if (key == NULL)
                return 0;
        key_n = u_collation_key(key, key_n + 1, string, n, locale);
        if (errno != 0) {
                free(key);
                return 0;
        }
        *result = key;
        return key_n;
}

int
u_collate(const char *a, size_t a_n, const char *b, size_t b_n,
          const char *locale)
{
        char a_buf[2048];
        char *a_key;
        size_t a_key_n = ckey(&a_key, a_buf, sizeof(a_buf), a, a_n, locale);
        int a_errno = errno;

        char b_buf[2048];
        char *b_key;
        size_t b_key_n = ckey(&b_key, b_buf, sizeof(b_buf), b, b_n, locale);
        int b_errno = errno;

        int r;
        if (a_errno != 0) {
                if (b_errno != 0)
                        r = compare(a, a_n, b, b_n);
                else
                        r = 1;
                errno = a_errno;
        } else if (b_errno != 0) {
                r = -1;
                errno = b_errno;
        } else
                r = compare(a_key, a_key_n, b_key, b_key_n);

        if (a_key != a_buf)
                free(a_key);
        if (b_key != b_buf)
                free(b_key);

        return r;
}
