#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "grapheme-break.h"


#define ROW(other, cr, lf, control, l, v, lv, lvt, t, regional_indicator, \
            prepend, extend, spacingmark) \
        { [UNICODE_GRAPHEME_BREAK_OTHER] = other, \
          [UNICODE_GRAPHEME_BREAK_CR] = cr, \
          [UNICODE_GRAPHEME_BREAK_LF] = lf, \
          [UNICODE_GRAPHEME_BREAK_CONTROL] = control, \
          [UNICODE_GRAPHEME_BREAK_L] = l, \
          [UNICODE_GRAPHEME_BREAK_V] = v, \
          [UNICODE_GRAPHEME_BREAK_LV] = lv, \
          [UNICODE_GRAPHEME_BREAK_LVT] = lvt, \
          [UNICODE_GRAPHEME_BREAK_T] = t, \
          [UNICODE_GRAPHEME_BREAK_REGIONAL_INDICATOR] = regional_indicator, \
          [UNICODE_GRAPHEME_BREAK_EXTEND] = extend, \
          [UNICODE_GRAPHEME_BREAK_SPACINGMARK] = spacingmark, \
          [UNICODE_GRAPHEME_BREAK_PREPEND] = prepend }
#define K(s) (s | (1 << 4))
static const uint8_t gb_dfa[][UNICODE_GRAPHEME_BREAK_V + 1] = {
        ROW(  0 ,  1 ,  2 ,  2 ,  3 ,  4 ,  4 ,  5 ,  5 ,  6 ,  7 ,K(0),K(0)), // Other | Extend | SpacingMark
        ROW(  0 ,  1 ,K(2),  2 ,  3 ,  4 ,  4 ,  5 ,  5 ,  6 ,  7 ,  0 ,  0 ), // CR
        ROW(  0 ,  1 ,  2 ,  2 ,  3 ,  4 ,  4 ,  5 ,  5 ,  6 ,  7 ,  0 ,  0 ), // LF | Control
        ROW(  0 ,  1 ,  2 ,  2 ,K(3),K(4),K(4),K(5),  5 ,  6 ,  7 ,K(0),K(0)), // L
        ROW(  0 ,  1 ,  2 ,  2 ,  3 ,K(4),  4 ,  5 ,K(5),  6 ,  7 ,K(0),K(0)), // V | LV
        ROW(  0 ,  1 ,  2 ,  2 ,  3 ,  4 ,  4 ,  5 ,K(5),  6 ,  7 ,K(0),K(0)), // LVT | T
        ROW(  0 ,  1 ,  2 ,  2 ,  3 ,  4 ,  4 ,  5 ,  5 ,K(6),  7 ,K(0),K(0)), // Regional_Indicator
        ROW(K(0),  1 ,  2 ,  2 ,K(3),K(4),K(4),K(5),K(5),K(6),K(0),K(0),K(0)), // Prepend
};
#undef K

void
u_grapheme_breaks(const char *string, size_t n, UnicodeBreakFn fn, void *closure)
{
        const char *p = string;
        const char *end = p + n;
        uint8_t state = 2;
        while (p < end) {
                state = gb_dfa[state & 0xf][s_grapheme_break_type(u_aref_char(p))];
                if (state >> 4 != 1)
                        fn(p, closure);
                p = u_next(p);
        }
}