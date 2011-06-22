#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#define UNICODE_ISVALID(char)				\
	((char) < 0x110000 &&				\
	 (((char) & 0xffffff800) != 0xd800) &&		\
	 ((char) < 0xfdd0 || (char) > 0xfdef) &&	\
	 ((char) & 0xfffe) != 0xfffe)

#define CONTINUATION_CHAR do {						\
	if ((*(unsigned char *)p & 0xc0) != 0x80)	/* 10xxxxxx */	\
		goto error;						\
	val <<= 6;							\
	val |= (*(unsigned char *)p) & 0x3f;				\
} while (0)

static const char *
fast_validate(const char *str)
{
	unichar val = 0;
	unichar min = 0;
	const char *p;

	for (p = str; *p != '\0'; p++) {
		if (*(unsigned char *)p < 128)
			continue;

		const char *last = p;

		if ((*(unsigned char *)p & 0xe0) == 0xc0) {                     /* 110xxxxx */
			if (UNLIKELY((*(unsigned char *)p & 0x1e) == 0))
				goto error;
			p++;
			if (UNLIKELY((*(unsigned char *)p & 0xc0) != 0x80))     /* 10xxxxxx */
				goto error;
		} else {
			if ((*(unsigned char *)p & 0xf0) == 0xe0) {             /* 1110xxxx */
				min = (1 << 11);
				val = *(unsigned char *)p & 0x0f;
				goto two_remaining;
			} else if ((*(unsigned char *)p & 0xf8) == 0xf0) {      /* 11110xxx */
				min = (1 << 16);
				val = *(unsigned char *)p & 0x07;
			} else {
				goto error;
			}

			p++;
			CONTINUATION_CHAR;
two_remaining:
			p++;
			CONTINUATION_CHAR;
			p++;
			CONTINUATION_CHAR;

			if (UNLIKELY(val < min))
				goto error;

			if (UNLIKELY(!UNICODE_ISVALID(val)))
				goto error;
		}

		continue;
error:
		return last;
	}

	return p;
}

static const char *
fast_validate_len(const char *str, size_t max_len)
{
	unichar val = 0;
	unichar min = 0;
	const char *p;

	for (p = str; (size_t)(p - str) < max_len; p++) {
		if (*(unsigned char *)p < 128)
			continue;

		const char *last = p;

		if ((*(unsigned char *)p & 0xe0) == 0xc0) {                     /* 110xxxxx */
			if (UNLIKELY(max_len - (p - str) < 2))
				goto error;

			if (UNLIKELY((*(unsigned char *)p & 0x1e) == 0))
				goto error;
			p++;
			if (UNLIKELY((*(unsigned char *)p & 0xc0) != 0x80))     /* 10xxxxxx */
				goto error;
		} else {
			if ((*(unsigned char *)p & 0xf0) == 0xe0) {             /* 1110xxxx */
				if (UNLIKELY(max_len - (p - str) < 3))
					goto error;

				min = (1 << 11);
				val = *(unsigned char *)p & 0x0f;
				goto two_remaining;
			} else if ((*(unsigned char *)p & 0xf8) == 0xf0) {      /* 11110xxx */
				if (UNLIKELY(max_len - (p - str) < 4))
					goto error;

				min = (1 << 16);
				val = *(unsigned char *)p & 0x07;
			} else {
				goto error;
			}

			p++;
			CONTINUATION_CHAR;
two_remaining:
			p++;
			CONTINUATION_CHAR;
			p++;
			CONTINUATION_CHAR;

			if (UNLIKELY(val < min))
				goto error;
			if (UNLIKELY(!UNICODE_ISVALID(val)))
				goto error;
		}

		continue;
error:
		return last;
	}

	return p;
}


/*
 * Check if STR constitutes a valid UTF-8 character sequence.
 */
bool
u_isvalid(const char *str)
{
	return *fast_validate(str) == '\0';
}


/*
 * Check if STR constitutes a valid UTF-8 character sequence, examining at most
 * MAX bytes.  If it turns out STR isn’t a valid UTF-8 character sequence and
 * END is non-‹NULL›, END is set to the end of the valid range of bytes in STR.
 */
bool
u_isvalid_n(const char *str, size_t max, const char **end)
{
        const char *p = fast_validate_len(str, max);

	if (end != NULL)
		*end = p;

	return p == str + max;
}
