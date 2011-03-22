#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
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

	unichar *a_norm = _utf_normalize_wc(a, 0, false, NORMALIZE_ALL_COMPOSE);
	unichar *b_norm = _utf_normalize_wc(b, 0, false, NORMALIZE_ALL_COMPOSE);

	int result = wcscoll((wchar_t *)a_norm, (wchar_t *)b_norm);

	free(a_norm);
	free(b_norm);

	return result;
}


/* {{{1
 * We need UTF-8 encoding of numbers to encode the weights if
 * we are using wcsxfrm. However, we aren't encoding Unicode
 * characters, so we can't simply use unichar_to_utf.
 *
 * The following routine is taken (with modification) from GNU
 * libc's strxfrm routine:
 *
 * Copyright (C) 1995-1999,2000,2001 Free Software Foundation, Inc.
 * Written by Ulrich Drepper <drepper@cygnus.com>, 1995.
 */
static inline int
_utf_encode(char *buf, wchar_t c)
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


/* {{{1
 * Generate a collation key from a string which can be compared with other
 * collation keys using str_compare().
 */
static char *
utf_collate_key_impl(const char *str, size_t len, bool use_len)
{
	assert(str != NULL);

	unichar *str_norm = _utf_normalize_wc(str, len, use_len, NORMALIZE_ALL_COMPOSE);
	size_t xfrm_len = wcsxfrm(NULL, (wchar_t *)str_norm, 0);
	wchar_t result_wc[xfrm_len + 1];
	wcsxfrm(result_wc, (wchar_t *)str_norm, xfrm_len + 1);

	int result_len = 0;
	for (size_t i = 0; i < xfrm_len; i++)
		result_len += _utf_encode(NULL, result_wc[i]);

	char *result = malloc(sizeof(char) * (result_len +1));
	result_len = 0;
	for (size_t i = 0; i < xfrm_len; i++)
		result_len += _utf_encode(result + result_len, result_wc[i]);
	result[result_len] = NUL;

	free(str_norm);

	return result;
}


/* {{{1
 * Generate a collation key from a string which can be compared with other
 * collation keys using str_compare().
 */
char *
u_collate_key(const char *str)
{
	return utf_collate_key_impl(str, 0, false);
}


/* {{{1
 * Generate a collation key from a string (of length ‘len’) which can be
 * compared with other collation keys using str_compare().
 */
char *
u_collate_key_n(const char *str, size_t len)
{
	return utf_collate_key_impl(str, len, true);
}
