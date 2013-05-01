#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "extconf.h"
#include <wchar.h>
#include <locale.h>
#ifdef HAVE_XLOCALE_H
#  include <xlocale.h>
#endif
#ifndef HAVE_WCSXFRM_L
static inline size_t
wcsxfrm_l(wchar_t *restrict ws1, wchar_t *restrict ws2, size_t n,
          UNUSED(locale_t loc))
{
        wcsxfrm(ws1, ws2, n);
}
#endif

#include "u.h"
#include "utf8.h"
#include "private.h"


/* {{{1
 * We need UTF-8 encoding of numbers to encode the weights if
 * we are using wcsxfrm. However, we aren't encoding Unicode
 * characters, so we can't simply use u_char_to_utf.
 *
 * The following routine is taken (with modification) from GNU
 * libc's strxfrm routine:
 *
 * Copyright (C) 1995-1999,2000,2001 Free Software Foundation, Inc.
 * Written by Ulrich Drepper <drepper@cygnus.com>, 1995.
 */
static inline int
utf8_encode(char *buf, wchar_t c)
{
	int retval;

	if (c < 0x80) {
		if (buf != NULL)
			*buf++ = (char)c;
		retval = 1;
	} else {
		int step;

		for (step = 2; step < 6; step++) {
			if ((c & (~(uint32_t)0 << (5 * step + 1))) == 0)
				break;
		}

		retval = step;

		if (buf != NULL) {
			*buf = (unsigned char)(~0xff >> step);
			step--;
			do {
				c = PUT_X(c, buf[step]);
			} while (--step > 0);
			*buf |= c;
		}
	}

	return retval;
}

static size_t
key(wchar_t *result, const wchar_t *string, size_t n, locale_t locale)
{
        return locale != NULL ?
                wcsxfrm_l(result, string, n, locale) :
                wcsxfrm(result, string, n);
}

/* {{{1
 * Generate a collation key from a string which can be compared with other
 * collation keys using str_compare().
 */
static char *
u_collation_key_impl(const char *str, size_t n, bool use_n, const char *locale,
                     size_t *new_n)
{
	assert(str != NULL);

        size_t norm_n;
	uint32_t *str_norm = _u_normalize_wc(str, n, use_n,
                                             U_NORMALIZE_ALL_COMPOSE,
                                             &norm_n);
        const uint32_t *p = str_norm;
        const uint32_t *end = str_norm + norm_n;
        uint32_t *q = str_norm;
        while (p < end) {
                if (*p != '\0')
                        *q++ = *p;
                p++;
        }
        *q = '\0';

        locale_t l = NULL;
        if (locale != NULL)
                l = newlocale(LC_COLLATE_MASK, locale, NULL);

	size_t xfrm_n = key(NULL, (wchar_t *)str_norm, 0, l);
	wchar_t *result_wc = malloc(sizeof(wchar_t) * (xfrm_n + 1));
        key(result_wc, (wchar_t *)str_norm, xfrm_n + 1, l);

	int result_n = 0;
	for (size_t i = 0; i < xfrm_n; i++)
		result_n += utf8_encode(NULL, result_wc[i]);

	char *result = malloc(sizeof(char) * (result_n + 1));
	result_n = 0;
	for (size_t i = 0; i < xfrm_n; i++)
		result_n += utf8_encode(result + result_n, result_wc[i]);
	result[result_n] = '\0';

        free(result_wc);
	free(str_norm);

        if (new_n != NULL)
                *new_n = result_n;

	return result;
}


/* {{{1
 * Generate a collation key from a string which can be compared with other
 * collation keys using str_compare().
 */
char *
u_collation_key(const char *str)
{
	return u_collation_key_impl(str, 0, false, NULL, NULL);
}


/* {{{1
 * Generate a collation key from a string (of length ‘len’) which can be
 * compared with other collation keys using str_compare().
 */
char *
u_collation_key_n(const char *str, size_t n, size_t *new_n)
{
	return u_collation_key_impl(str, n, true, NULL, new_n);
}

char *
u_collation_key_in_locale_n(const char *str, size_t n, const char *locale,
                            size_t *new_n)
{
        return u_collation_key_impl(str, n, true, locale, new_n);
}
