#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "u.h"
#include "utf8.h"
#include "private.h"


/* {{{1
 * Private function used to calculate the length and mask to use when dealing
 * with a given UTF-8 character sequence.
 */
static inline void
_utf_compute(unsigned char c, int *mask, int *len)
{
	if (c < 0x80) {
		*len = 1;
		*mask = 0x7f;
	} else if ((c & 0xe0) == 0xc0) {
		*len = 2;
		*mask = 0x1f;
	} else if ((c & 0xf0) == 0xe0) {
		*len = 3;
		*mask = 0x0f;
	} else if ((c & 0xf8) == 0xf0) {
		*len = 4;
		*mask = 0x07;
	} else if ((c & 0xfc) == 0xf8) {
		*len = 5;
		*mask = 0x03;
	} else if ((c & 0xfe) == 0xfc) {
		*len = 6;
		*mask = 0x01;
	} else {
		*len = -1;
	}
}


/* {{{1
 * Private function used to retrieve a UTF-32 character from an UTF-8 character
 * sequence given a mask and length previously retrieved with _utf_compute().
 */
static inline unichar
_utf_get(const char *str, int mask, int len)
{
	unichar c = (unsigned char)str[0] & mask;

	for (int i = 1; i < len; i++) {
		unsigned char ch = ((const unsigned char *)str)[i];

		if (CONT_X(ch)) {
			c = ADD_X(c, ch);
		} else {
			c = UTF_BAD_INPUT_UNICHAR;
			break;
		}
	}

	return c;
}


/* {{{1
 * Retrieve a UTF-32 character from a UTF-8 character sequence.
 */
unichar
u_aref_char(const char *str)
{
	int mask;
	int len;

	_utf_compute(*str, &mask, &len);

	return (len > -1) ? _utf_get(str, mask, len) : UTF_BAD_INPUT_UNICHAR;
}


/* {{{1
 * TODO
 */
unichar
u_aref_char_n(const char *str, size_t max)
{
        if (max == 0)
                return UTF_INCOMPLETE_INPUT_UNICHAR;

	size_t len;
	unichar c = (unsigned char)*str;

	/* TODO: _utf_compute() here */
	if (c < 0x80) {
		return c;
	} else if (c < 0xc0) {
		return UTF_BAD_INPUT_UNICHAR;
	} else if (c < 0xe0) {
		len = 2;
		c &= 0x1f;
	} else if (c < 0xf0) {
		len = 3;
		c &= 0x0f;
	} else if (c < 0xf8) {
		len = 4;
		c &= 0x07;
	} else if (c < 0xfc) {
		len = 5;
		c &= 0x03;
	} else if (c < 0xfe) {
		len = 6;
		c &= 0x01;
	} else {
		return UTF_BAD_INPUT_UNICHAR;
	}

	if (len > max) {
		for (size_t i = 1; i < max; i++) {
			if (!CONT_X(str[i]))
				return UTF_BAD_INPUT_UNICHAR;
		}

		return UTF_INCOMPLETE_INPUT_UNICHAR;
	}

	for (size_t i = 1; i < len; i++) {
		unsigned char ch = ((const unsigned char *)str)[i];

		if (!CONT_X(ch))
			return (ch != NUL) ? UTF_BAD_INPUT_UNICHAR : UTF_INCOMPLETE_INPUT_UNICHAR;

		c = ADD_X(c, ch);
	}

	return (_utf8_length(c) == len) ? c : UTF_BAD_INPUT_UNICHAR;
}


/* {{{1
 * Retrieve a UTF-32 character from a UTF-8 character sequence.  This function
 * does additional checking while converitng, such as not overruning a maximum
 * length and checks for incomplete, invalid or out-of-range characters.
 */
unichar
u_aref_char_validated(const char *str)
{
	unichar result = u_aref_char(str);

	if (result & 0x80000000) {
		return result;
	} else if (!unichar_isvalid(result)) {
		return UTF_BAD_INPUT_UNICHAR;
	} else {
		return result;
	}
}


/* {{{1 */
unichar
u_aref_char_validated_n(const char *str, size_t max)
{
	unichar result = u_aref_char_n(str, max);

	if (result & 0x80000000) {
		return result;
	} else if (!unichar_isvalid(result)) {
		return UTF_BAD_INPUT_UNICHAR;
	} else {
		return result;
	}
}
