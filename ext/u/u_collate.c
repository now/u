#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "extconf.h"
#include <wchar.h>
#include <locale.h>
#ifdef HAVE_XLOCALE_H
#  include <xlocale.h>
#endif
#ifndef HAVE_WCSCOLL_L
static inline size_t
wcscoll_l(wchar_t *restrict ws1, wchar_t *restrict ws2, size_t n,
          UNUSED(locale_t loc))
{
        wcsxfrm(ws1, ws2, n);
}
#endif

#include "u.h"
#include "utf8.h"
#include "private.h"

static int
collate(uint32_t *a, uint32_t *b, locale_t locale)
{
        return locale != NULL ?
                wcscoll_l((wchar_t *)a, (wchar_t *)b, locale) :
                wcscoll((wchar_t *)a, (wchar_t *)b);
}

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

        int result = collate(a_norm, b_norm, NULL);

	free(a_norm);
	free(b_norm);

	return result;
}

int
u_collate_in_locale_n(const char *a, size_t a_n, const char *b, size_t b_n,
                      const char *locale)
{
        size_t a_norm_n;
	uint32_t * const a_norm = _u_normalize_wc(a, a_n, true,
                                                  U_NORMALIZE_ALL_COMPOSE,
                                                  &a_norm_n);

        size_t b_norm_n;
	uint32_t * const b_norm = _u_normalize_wc(b, b_n, true,
                                                  U_NORMALIZE_ALL_COMPOSE,
                                                  &b_norm_n);

        locale_t l = NULL;
        if (locale != NULL)
                l = newlocale(LC_COLLATE_MASK, locale, NULL);

        int result = 0;

        uint32_t *a_p = a_norm;
        uint32_t *a_end = a_norm + a_norm_n;
        uint32_t *b_p = b_norm;
        uint32_t *b_end = b_norm + b_norm_n;
        while (a_p <= a_end && b_p <= b_end) {
                result = collate(a_p, b_p, l);
                if (result != 0)
                        break;
                a_p += wcslen((wchar_t *)a_p) + 1;
                b_p += wcslen((wchar_t *)b_p) + 1;
        }

        if (l != NULL)
                freelocale(l);
	free(a_norm);
	free(b_norm);

	return result;
}

int
u_collate_n(const char *a, size_t a_n, const char *b, size_t b_n)
{
        return u_collate_in_locale_n(a, a_n, b, b_n, NULL);
}
