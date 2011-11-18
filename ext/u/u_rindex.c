#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "u.h"
#include "private.h"

/*
 * Retrieve the index/offset of the right-most occurence of NEEDLE in
 * HAYSTACK, or -1 if it doesn’t exist.
 */
static size_t
str_rindex(const char *haystack, const char *needle)
{
	assert(haystack != NULL);
	assert(needle != NULL);

	size_t needle_len = strlen(needle);
	size_t haystack_len = strlen(haystack);

	if (needle_len == 0)
		return haystack_len;

	if (haystack_len < needle_len)
		return -1;

	for (const char *p = haystack + haystack_len - needle_len; p >= haystack; p--) {
		size_t i;

		for (i = 0; i < needle_len; i++) {
			if (p[i] != needle[i])
				break;
		}

		if (i == needle_len)
			return p - haystack;
	}

	return -1;
}


/*
 * Retrieve the index/offset of the right-most occurence of NEEDLE in
 * HAYSTACK, or -1 if it doesn’t exist.
 */
static size_t
str_rindex_n(const char *haystack, const char *needle, size_t haystack_len)
{
	assert(haystack != NULL);
	assert(needle != NULL);

	size_t needle_len = strlen(needle);
	const char *haystack_max = haystack + haystack_len;
	const char *p = haystack;

	while (p < haystack_max && *p != '\0')
		p++;

	if (p < haystack + needle_len)
		return -1;

	p -= needle_len;

	for ( ; p >= haystack; p--) {
		size_t i;

		for (i = 0; i < needle_len; i++) {
			if (p[i] != needle[i])
				break;
		}

		if (i == needle_len)
			return p - haystack;
	}

	return -1;
}


/* {{{1
 * Retrieve the index of the right-most occurence of ‘c’ in ‘str’, or -1 if it
 * doesn't exist.
 */
size_t
u_char_rindex(const char *str, unichar c)
{
	char ch[7];

	ch[unichar_to_u(c, ch)] = '\0';

	return str_rindex(str, ch);
}


/* {{{1
 * Retrieve the index of the right-most occurence of ‘c’ in ‘str’, or -1 if it
 * doesn't exist, going over at most ‘len’ bytes in ‘str’.
 */
size_t
u_char_rindex_n(const char *str, unichar c, size_t len)
{
	char ch[7];

	ch[unichar_to_u(c, ch)] = '\0';

	return str_rindex_n(str, ch, len);
}


/* {{{1
 * Retrieve the index of the right-most occurence of ‘needle’ in ‘haystack’, or
 * -1 if it doesn't exist.
 */
size_t
u_rindex(const char *haystack, const char *needle)
{
	return str_rindex(haystack, needle);
}


/* {{{1
 * Retrieve the index of the right-most occurence of ‘needle’ in ‘haystack’, or
 * -1 if it doesn't exist, going over at most ‘len’ bytes in ‘haystack’.
 */
size_t
u_rindex_n(const char *haystack, const char *needle, size_t len)
{
	return str_rindex_n(haystack, needle, len);
}
