#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

static bool
u_is_ascii_only_impl(const char *string, size_t length, bool use_length)
{
        const char *p = string;
        const char *end = p + length;
        while (P_WITHIN_STR(p, end, use_length)) {
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
u_is_ascii_only_n(const char *string, size_t length)
{
        return u_is_ascii_only_impl(string, length, true);
}
