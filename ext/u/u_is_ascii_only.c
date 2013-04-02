#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

static bool
u_is_ascii_only_impl(const char *string, size_t n, bool use_n)
{
        const char *p = string;
        const char *end = p + n;
        while (P_WITHIN_STR(p, end, use_n)) {
                if (*(unsigned char *)p > 127)
                        return false;

                p++;
        }

        return true;
}

bool
u_is_ascii_only(const char *string)
{
        return u_is_ascii_only_impl(string, 0, false);
}

bool
u_is_ascii_only_n(const char *string, size_t n)
{
        return u_is_ascii_only_impl(string, n, true);
}
