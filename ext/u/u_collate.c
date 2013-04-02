#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "u.h"
#include "utf8.h"
#include "private.h"

/* {{{1
 * Compare two strings for ordering using the linguistically correct rules of
 * the current locale.
 */
int
u_collate(const char *a, const char *b)
{
	assert(a != NULL);
	assert(b != NULL);

	uint32_t *a_norm = _u_normalize_wc(a, 0, false, U_NORMALIZE_ALL_COMPOSE, NULL);
	uint32_t *b_norm = _u_normalize_wc(b, 0, false, U_NORMALIZE_ALL_COMPOSE, NULL);

	int result = wcscoll((wchar_t *)a_norm, (wchar_t *)b_norm);

	free(a_norm);
	free(b_norm);

	return result;
}


int
u_collate_n(const char *a, size_t a_n, const char *b, size_t b_n)
{
        size_t a_norm_n;
	uint32_t * const a_norm = _u_normalize_wc(a, a_n, true,
                                                  U_NORMALIZE_ALL_COMPOSE,
                                                  &a_norm_n);

        size_t b_norm_n;
	uint32_t * const b_norm = _u_normalize_wc(b, b_n, true,
                                                  U_NORMALIZE_ALL_COMPOSE,
                                                  &b_norm_n);

        int result = 0;

        uint32_t *a_p = a_norm;
        uint32_t *a_end = a_norm + a_norm_n;
        uint32_t *b_p = b_norm;
        uint32_t *b_end = b_norm + b_norm_n;
        while (a_p <= a_end && b_p <= b_end) {
                result = wcscoll((wchar_t *)a_p, (wchar_t *)b_p);
                if (result != 0)
                        break;
                a_p += wcslen((wchar_t *)a_p) + 1;
                b_p += wcslen((wchar_t *)b_p) + 1;
        }

	free(a_norm);
	free(b_norm);

	return result;
}
