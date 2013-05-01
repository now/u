#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "general-category.h"


/* {{{1
 * Determine whether ‘c’ is an alphanumeric, such as A, B, C, 0, 1, or 2.
 */
bool
u_char_isalnum(uint32_t c)
{
        return IS(s_general_category(c),
                  OR(U_GENERAL_CATEGORY_NUMBER_DECIMAL,
                     OR(U_GENERAL_CATEGORY_NUMBER_LETTER,
                        OR(U_GENERAL_CATEGORY_NUMBER_OTHER,
                           OR(U_GENERAL_CATEGORY_LETTER_LOWERCASE,
                              OR(U_GENERAL_CATEGORY_LETTER_UPPERCASE,
                                 OR(U_GENERAL_CATEGORY_LETTER_TITLECASE,
                                    OR(U_GENERAL_CATEGORY_LETTER_MODIFIER,
                                       OR(U_GENERAL_CATEGORY_LETTER_OTHER, 0)))))))));
}
