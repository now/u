#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "u.h"
#include "private.h"


static size_t
u_width_impl(const char *string, size_t length, bool use_length)
{
	assert(string != NULL);

	size_t width = 0;

        const char *p = string;
        const char *end = p + length;
        while (P_WITHIN_STR(p, end, use_length)) {
                unichar c = u_aref_char(p);

		width += unichar_iswide(c) ? 2 : unichar_iszerowidth(c) ? 0 : 1;

                p = u_next(p);
        }

	return width;
}

size_t
u_width(const char *string)
{
	return u_width_impl(string, 0, false);
}

size_t
u_width_n(const char *string, size_t length)
{
	return u_width_impl(string, length, true);
}
