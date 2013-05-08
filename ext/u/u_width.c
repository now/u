#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "u.h"
#include "private.h"


static size_t
u_width_impl(const char *string, size_t n, bool use_n)
{
	assert(string != NULL);

	size_t width = 0;

        const char *p = string;
        const char *end = p + n;
        while (P_WITHIN_STR(p, end, use_n)) {
                uint32_t c;
                p = u_decode(&c, p, end);
		width += u_char_width(c);
        }

	return width;
}

size_t
u_width(const char *string)
{
	return u_width_impl(string, 0, false);
}

size_t
u_width_n(const char *string, size_t n)
{
	return u_width_impl(string, n, true);
}
