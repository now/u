#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "word-break.h"


#define ROW(other, cr, lf, newline, aletter, numeric, katakana, extendnumlet, \
            regional_indicator, midletter, midnumlet, midnum, format, extend) \
        { [U_WORD_BREAK_OTHER] = other, \
          [U_WORD_BREAK_CR] = cr, \
          [U_WORD_BREAK_LF] = lf, \
          [U_WORD_BREAK_NEWLINE] = newline, \
          [U_WORD_BREAK_FORMAT] = format, \
          [U_WORD_BREAK_EXTEND] = extend, \
          [U_WORD_BREAK_ALETTER] = aletter, \
          [U_WORD_BREAK_NUMERIC] = numeric, \
          [U_WORD_BREAK_KATAKANA] = katakana, \
          [U_WORD_BREAK_EXTENDNUMLET] = extendnumlet, \
          [U_WORD_BREAK_REGIONAL_INDICATOR] = regional_indicator, \
          [U_WORD_BREAK_MIDLETTER] = midletter, \
          [U_WORD_BREAK_MIDNUMLET] = midnumlet, \
          [U_WORD_BREAK_MIDNUM] = midnum }
#define K(s) (s | (1 << 4))
#define S(s) (s | (2 << 4))
#define D(s) (s | (3 << 4))
static const uint8_t wb_dfa[][U_WORD_BREAK_REGIONAL_INDICATOR + 1] = {
        ROW(0,1,  2 ,2,  3 ,  4 ,  5 ,  6 ,  7 ,  0 ,  0 ,  0 ,K(0),K(0)), // Other
        ROW(0,1,K(2),2,  3 ,  4 ,  5 ,  6 ,  7 ,  0 ,  0 ,  0 ,  0 ,  0 ), // CR
        ROW(0,1,  2 ,2,  3 ,  4 ,  5 ,  6 ,  7 ,  0 ,  0 ,  0 ,  0 ,  0 ), // LF | Newline
        ROW(0,1,  2 ,2,K(3),K(4),  5 ,K(6),  7 ,S(8),S(8),  0 ,K(3),K(3)), // ALetter
        ROW(0,1,  2 ,2,K(3),K(4),  5 ,K(6),  7 ,  0 ,S(9),S(9),K(4),K(4)), // Numeric
        ROW(0,1,  2 ,2,  3 ,  4 ,K(5),K(6),  7 ,  0 ,  0 ,  0 ,K(5),K(5)), // Katakana
        ROW(0,1,  2 ,2,K(3),K(4),K(5),K(6),  7 ,  0 ,  0 ,  0 ,K(6),K(6)), // ExtendNumLet
        ROW(0,1,  2 ,2,  3 ,  4 ,  5 ,  6 ,K(7),  0 ,  0 ,  0 ,K(7),K(7)), // Regional_Indicator
        ROW(0,1,  2 ,2,D(3),  4 ,  5 ,  6 ,  7 ,  0 ,  0 ,  0 ,K(8),K(8)), // ALetter (MidLetter | MidNumLet)
        ROW(0,1,  2 ,2,  3 ,D(4),  5 ,  6 ,  7 ,  0 ,  0 ,  0 ,K(9),K(9)), // Numeric (MidNum | MidNumLet)
};
#undef D
#undef S
#undef K

void
u_word_breaks(const char *string, size_t n, u_break_fn fn, void *closure)
{
        const char *p = string;
        const char *end = p + n;
        const char *s = NULL;
        uint8_t state = 2;
        while (p < end) {
                state = wb_dfa[state & 0xf][s_word_break(u_dref(p))];
                switch (state >> 4) {
                case 1:
                        break;
                case 2:
                        s = p;
                        break;
                case 3:
                        s = NULL;
                        break;
                default:
                        if (s != NULL) {
                                fn(s, closure);
                                s = NULL;
                        }
                        fn(p, closure);
                }
                p = u_next(p);
        }
        if (s != NULL)
                fn(s, closure);
}
