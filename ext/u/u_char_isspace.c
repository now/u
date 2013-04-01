#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "general-category.h"


/* {{{1
 * Determine whether ‘c’ is some form of whitespace, such as space, tab or a
 * line separator (newline, carriage return, etc.).
 */
bool
u_char_isspace(uint32_t c)
{
	switch (c) {
	case '\t':
	case '\n':
	case '\r':
	case '\f':
		return true;
	default:
                return IS(s_general_category(c),
                          OR(U_GENERAL_CATEGORY_SEPARATOR_SPACE,
                             OR(U_GENERAL_CATEGORY_SEPARATOR_LINE,
                                OR(U_GENERAL_CATEGORY_SEPARATOR_PARAGRAPH, 0)))) ? true : false;
	}
}
