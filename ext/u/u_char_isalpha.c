#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"


/* {{{1
 * Determine whether ‘c’ is an alphabetic (i.e. a letter), such as A, B, or C.
 */
bool
u_char_isalpha(uint32_t c)
{
        return IS(u_char_general_category(c),
                  OR(U_GENERAL_CATEGORY_LETTER_LOWERCASE,
                     OR(U_GENERAL_CATEGORY_LETTER_UPPERCASE,
                        OR(U_GENERAL_CATEGORY_LETTER_TITLECASE,
                           OR(U_GENERAL_CATEGORY_LETTER_MODIFIER,
                              OR(U_GENERAL_CATEGORY_LETTER_OTHER, 0))))));
}
