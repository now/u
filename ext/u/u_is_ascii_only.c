#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

static bool
u_is_ascii_only_impl(const char *string, size_t length, bool use_length)
{
        for (const char *p = string; P_WITHIN_STR(p, string, length, use_length); p++)
                if (*p & 0x80)
                        return false;

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
