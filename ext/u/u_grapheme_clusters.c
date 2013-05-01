#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"


#define ROW(other, cr, lf, control, l, v, lv, lvt, t, regional_indicator, \
            prepend, extend, spacingmark) \
        { [U_GRAPHEME_BREAK_OTHER] = other, \
          [U_GRAPHEME_BREAK_CR] = cr, \
          [U_GRAPHEME_BREAK_LF] = lf, \
          [U_GRAPHEME_BREAK_CONTROL] = control, \
          [U_GRAPHEME_BREAK_L] = l, \
          [U_GRAPHEME_BREAK_V] = v, \
          [U_GRAPHEME_BREAK_LV] = lv, \
          [U_GRAPHEME_BREAK_LVT] = lvt, \
          [U_GRAPHEME_BREAK_T] = t, \
          [U_GRAPHEME_BREAK_REGIONAL_INDICATOR] = regional_indicator, \
          [U_GRAPHEME_BREAK_EXTEND] = extend, \
          [U_GRAPHEME_BREAK_SPACINGMARK] = spacingmark, \
          [U_GRAPHEME_BREAK_PREPEND] = prepend }
#define K(s) (s | (1 << 4))
static const uint8_t gb_dfa[][U_GRAPHEME_BREAK_V + 1] = {
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
u_grapheme_clusters(const char *string, size_t n, u_substring_fn fn, void *closure)
{
        const char *p = string;
        const char *q = p;
        const char *end = p + n;
        uint8_t state = 2;
        while (q < end) {
                state = gb_dfa[state & 0xf][u_char_grapheme_break(u_dref(q))];
                if (state >> 4 != 1) {
                        if (p < q)
                                fn(p, q - p, closure);
                        p = q;
                }
                q = u_next(q);
        }
        if (p < q)
                fn(p, q - p, closure);
}
