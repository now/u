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
                  OR(UNICODE_CONNECT_PUNCTUATION,
                     OR(UNICODE_DASH_PUNCTUATION,
                        OR(UNICODE_OPEN_PUNCTUATION,
                           OR(UNICODE_CLOSE_PUNCTUATION,
                              OR(UNICODE_INITIAL_PUNCTUATION,
                                 OR(UNICODE_FINAL_PUNCTUATION,
                                    OR(UNICODE_OTHER_PUNCTUATION,
                                       OR(UNICODE_MODIFIER_SYMBOL,
                                          OR(UNICODE_MATH_SYMBOL,
                                             OR(UNICODE_CURRENCY_SYMBOL,
                                                OR(UNICODE_OTHER_SYMBOL, 0)))))))))))) ? true : false;
}
