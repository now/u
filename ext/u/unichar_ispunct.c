#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "types.h"


/* {{{1
 * Determine whether ‘c’ is some form of punctuation or other symbol.
 */
bool
unichar_ispunct(unichar c)
{
        return IS(s_type(c),
                  OR(U_PUNCTUATION_CONNECTOR,
                     OR(U_PUNCTUATION_DASH,
                        OR(U_PUNCTUATION_OPEN,
                           OR(U_PUNCTUATION_CLOSE,
                              OR(U_PUNCTUATION_INITIAL_QUOTE,
                                 OR(U_PUNCTUATION_FINAL_QUOTE,
                                    OR(U_PUNCTUATION_OTHER,
                                       OR(U_SYMBOL_MODIFIER,
                                          OR(U_SYMBOL_MATH,
                                             OR(U_SYMBOL_CURRENCY,
                                                OR(U_SYMBOL_OTHER, 0)))))))))))) ? true : false;
}
