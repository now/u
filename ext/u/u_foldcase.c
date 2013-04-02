#include <ruby.h>
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"

#include "private.h"

#include "data/case-folding.h"


static inline bool
casefold_table_lookup(uint32_t c, char *result, size_t *n)
{
        size_t index;
        if (!unicode_table_lookup(casefold_table, c, &index))
                return false;

        char const *folded = casefold_table[index].data;
        if (result != NULL)
                strcpy(result, folded);
        *n += u_byte_length(folded);

        return true;
}

static size_t
foldcase_loop(const char *string, const char *end, bool use_end, char *result)
{
	size_t n = 0;

        for (const char *p = string; P_WITHIN_STR(p, end, use_end); p = u_next(p)) {
		uint32_t c = u_aref_char(p);
                if (!casefold_table_lookup(c, OFFSET_IF(result, n), &n))
                        n += u_char_to_u(u_char_tolower(c), OFFSET_IF(result, n));
	}

        return n;
}

static char *
u_foldcase_impl(const char *string, size_t n, bool use_n,
                size_t *new_n)
{
	assert(string != NULL);

        const char *end = string + n;
	size_t m = foldcase_loop(string, end, use_n, NULL);
        char *result = ALLOC_N(char, m + 1);
        foldcase_loop(string, end, use_n, result);
        result[m] = '\0';

        if (new_n != NULL)
                *new_n = m;

	return result;
}

char *
u_foldcase(const char *string)
{
	return u_foldcase_impl(string, 0, false, NULL);
}

char *
u_foldcase_n(const char *string, size_t n, size_t *new_n)
{
	return u_foldcase_impl(string, n, true, new_n);
}
