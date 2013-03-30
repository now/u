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
                  OR(U_CONNECT_PUNCTUATION,
                     OR(U_DASH_PUNCTUATION,
                        OR(U_OPEN_PUNCTUATION,
                           OR(U_CLOSE_PUNCTUATION,
                              OR(U_INITIAL_PUNCTUATION,
                                 OR(U_FINAL_PUNCTUATION,
                                    OR(U_OTHER_PUNCTUATION,
                                       OR(U_MODIFIER_SYMBOL,
                                          OR(U_MATH_SYMBOL,
                                             OR(U_CURRENCY_SYMBOL,
                                                OR(U_OTHER_SYMBOL, 0)))))))))))) ? true : false;
}
