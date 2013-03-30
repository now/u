#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "types.h"


/* {{{1
 * Determine whether ‘c’ is some form of whitespace, such as space, tab or a
 * line separator (newline, carriage return, etc.).
 */
bool
unichar_isspace(unichar c)
{
	switch (c) {
	case '\t':
	case '\n':
	case '\r':
	case '\f':
		return true;
	default:
                return IS(s_type(c),
                          OR(U_SPACE_SEPARATOR,
                             OR(U_LINE_SEPARATOR,
                                OR(U_PARAGRAPH_SEPARATOR, 0)))) ? true : false;
	}
}
