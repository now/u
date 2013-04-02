/* {{{1
 * These are a couple of constants we use for dealing with the bit-twiddling
 * necessary when dealing with UTF-8 character sequences.
 */
enum {
	BIT_1 = 7,
	BIT_X = 6,
	BIT_2 = 5,
	BIT_3 = 4,
	BIT_4 = 3,
	BIT_5 = 2,
	BIT_6 = 1,

	OCT_1 = ((1 << (BIT_1 + 1)) - 1) ^ 0xff,	/* 0000 0000 */
	OCT_X = ((1 << (BIT_X + 1)) - 1) ^ 0xff,	/* 1000 0000 */
	OCT_2 = ((1 << (BIT_2 + 1)) - 1) ^ 0xff,	/* 1100 0000 */
	OCT_3 = ((1 << (BIT_3 + 1)) - 1) ^ 0xff,	/* 1110 0000 */
	OCT_4 = ((1 << (BIT_4 + 1)) - 1) ^ 0xff,	/* 1111 0000 */
	OCT_5 = ((1 << (BIT_5 + 1)) - 1) ^ 0xff,	/* 1111 1000 */
	OCT_6 = ((1 << (BIT_6 + 1)) - 1) ^ 0xff,	/* 1111 1100 */

	UNI_LEN1 = 0x80,
	UNI_LEN2 = 0x800,
	UNI_LEN3 = 0x10000,
	UNI_LEN4 = 0x200000,
	UNI_LEN5 = 0x4000000,

	MASK_X = (1 << BIT_X) - 1,			/* 0011 1111 */
	TEST_X = MASK_X ^ 0xff,				/* 1100 0000 */
};

/* {{{1
 * Determine whether ‘p’ is part of a UTF-8 multi-byte sequence.
 */
#define CONT_X(p)	((((unsigned char)p) & TEST_X) == OCT_X)

/* {{{1
 * Put bits from ‘c’ into ‘p’ and shift them off of ‘c’ afterwards.
 */
#define PUT_X(c, p)	((p) = OCT_X | ((c) & MASK_X), (c) >> BIT_X)

/* {{{1
 * Private function used to figure out the length of the UTF-8 representation
 * of a given Unicode character (UTF-32).
 */
static inline unsigned short
_utf8_length(const uint32_t c)
{
	if (c < UNI_LEN1)
		return 1;
	else if (c < UNI_LEN2)
		return 2;
	else if (c < UNI_LEN3)
		return 3;
	else if (c < UNI_LEN4)
		return 4;
	else if (c < UNI_LEN5)
		return 5;
	else
		return 6;
}
