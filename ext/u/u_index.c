#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "u.h"
#include "private.h"

/* {{{1
 * Retrieve the offset/index of ‘needle’ in ‘haystack’ which is of size
 * ‘haystack_len’.
 */
static U_PURE size_t
str_index_n(const char *haystack, const char *needle, size_t haystack_n)
{
	assert(haystack != NULL);
	assert(needle != NULL);

	size_t needle_n = strlen(needle);

	if (needle_n == 0)
		return 0;

	if (haystack_n < needle_n)
		return -1;

	const char *end = haystack + haystack_n - needle_n;
	for (const char *p = haystack; *p != '\0' && p <= end; p++) {
		size_t i;

		for (i = 0; i < needle_n; i++) {
			if (p[i] != needle[i])
				break;
		}

		if (i == needle_n)
			return p - haystack;
	}

	return -1;
}


/* {{{1
 * Retrieve the index of the left-most occurence of ‘c’ in ‘str’, or -1 if it
 * doesn't exist.
 */
size_t
u_char_index(const char *str, uint32_t c)
{
	char ch[7];

	ch[u_char_to_u(c, ch)] = '\0';
	char *p = strstr(str, ch);
	return (p != NULL) ? p - str : -1;
}


/* {{{1
 * Retrieve the index of the left-most occurence of ‘c’ in ‘str’, or -1 if it
 * doesn't exist, going over at most ‘len’ bytes in ‘str’.
 */
size_t
u_char_index_n(const char *str, uint32_t c, size_t n)
{
	char ch[7];

	ch[u_char_to_u(c, ch)] = '\0';

	return str_index_n(str, ch, n);
}


/* {{{1
 * Retrieve the index of the left-most occurence of ‘needle’ in ‘haystack’, or
 * -1 if it doesn't exist.
 */
size_t
u_index(const char *haystack, const char *needle)
{
	return strstr(haystack, needle) - haystack;
}


/* {{{1
 * Retrieve the index of the left-most occurence of ‘needle’ in ‘haystack’, or
 * -1 if it doesn't exist, going over at most ‘len’ bytes in ‘haystack’.
 */
size_t
u_index_n(const char *haystack, const char *needle, size_t n)
{
	return str_index_n(haystack, needle, n);
}
