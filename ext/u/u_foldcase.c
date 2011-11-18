#include <ruby.h>
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"

#include "private.h"

#include "data/case-folding.h"


static inline bool
casefold_table_lookup(unichar c, char *result, size_t *length)
{
        size_t index;
        if (!unicode_table_lookup(casefold_table, c, &index))
                return false;

        char const *folded = casefold_table[index].data;
        if (result != NULL)
                strcpy(result, folded);
        *length += u_byte_length(folded);

        return true;
}

static size_t
foldcase_loop(const char *string, size_t length, bool use_length, char *result)
{
	size_t n = 0;

        const char *p = string;
        const char *end = p + length;
        while (P_WITHIN_STR(p, end, use_length)) {
		unichar c = u_aref_char(p);
                if (!casefold_table_lookup(c, OFFSET_IF(result, n), &n))
                        n += unichar_to_u(unichar_tolower(c),
                                          OFFSET_IF(result, n));

                p = u_next(p);
	}

        return n;
}

static char *
u_foldcase_impl(const char *string, size_t length, bool use_length,
                size_t *new_length)
{
	assert(string != NULL);

	size_t n = foldcase_loop(string, length, use_length, NULL);
        char *result = ALLOC_N(char, n + 1);
        foldcase_loop(string, length, use_length, result);
        result[n] = '\0';

        if (new_length != NULL)
                *new_length = n;

	return result;
}

char *
u_foldcase(const char *string)
{
	return u_foldcase_impl(string, 0, false, NULL);
}

char *
u_foldcase_n(const char *string, size_t length, size_t *new_length)
{
	return u_foldcase_impl(string, length, true, new_length);
}
