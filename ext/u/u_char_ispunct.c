#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "general-category.h"


/* {{{1
 * Determine whether ‘c’ is some form of punctuation or other symbol.
 */
bool
u_char_ispunct(uint32_t c)
{
        return IS(s_general_category(c),
                  OR(U_GENERAL_CATEGORY_PUNCTUATION_CONNECTOR,
                     OR(U_GENERAL_CATEGORY_PUNCTUATION_DASH,
                        OR(U_GENERAL_CATEGORY_PUNCTUATION_OPEN,
                           OR(U_GENERAL_CATEGORY_PUNCTUATION_CLOSE,
                              OR(U_GENERAL_CATEGORY_PUNCTUATION_INITIAL_QUOTE,
                                 OR(U_GENERAL_CATEGORY_PUNCTUATION_FINAL_QUOTE,
                                    OR(U_GENERAL_CATEGORY_PUNCTUATION_OTHER,
                                       OR(U_GENERAL_CATEGORY_SYMBOL_MODIFIER,
                                          OR(U_GENERAL_CATEGORY_SYMBOL_MATH,
                                             OR(U_GENERAL_CATEGORY_SYMBOL_CURRENCY,
                                                OR(U_GENERAL_CATEGORY_SYMBOL_OTHER, 0)))))))))))) ? true : false;
}
