#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "u.h"

/* {{{1
 * Determine whether ‘c’ is a wide character, thus is typically rendered in a
 * double-width cell on a terminal.
 */
bool
unichar_iswide(unichar c)
{
	if (c < 0x1100)
		return false;

        return (c <= 0x115f || 				/* Hangul Jamo init. consonants */
                c == 0x2329 || c == 0x232a || 		/* angle brackets */
                (c >= 0x2e80 && c <= 0xa4cf && 		/* CJK ... Yi */
                 (c < 0x302a || c > 0x302f) &&
                 c != 0x303f && c != 0x3099 && c != 0x309a) ||
                (c >= 0xac00 && c <= 0xd7a3) || 	/* Hangul syllables */
                (c >= 0xf900 && c <= 0xfaff) || 	/* CJK comp. graphs */
                (c >= 0xfe30 && c <= 0xfe6f) || 	/* CJK comp. forms */
                (c >= 0xff00 && c <= 0xff60) || 	/* fullwidth forms */
                (c >= 0xffe0 && c <= 0xffe6) || 	/*       -"-       */
                (c >= 0x20000 && c <= 0x2fffd) || 	/* CJK extra stuff */
                (c >= 0x30000 && c <= 0x3fffd));    	/*       -"-       */
}
