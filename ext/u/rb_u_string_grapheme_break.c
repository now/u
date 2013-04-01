#include "rb_includes.h"

#define BREAK2ID(value, symbol) \
        case U_GRAPHEME_BREAK_##value: { \
                static ID id_##symbol; \
                if (id_##symbol == 0) \
                        id_##symbol = rb_intern(#symbol); \
                return ID2SYM(id_##symbol); \
        }

static VALUE
break_to_symbol(enum u_grapheme_break value)
{
        switch (value) {
        BREAK2ID(CONTROL, control)
        BREAK2ID(CR, cr)
        BREAK2ID(EXTEND, extend)
        BREAK2ID(L, l)
        BREAK2ID(LF, lf)
        BREAK2ID(LV, lv)
        BREAK2ID(LVT, lvt)
        BREAK2ID(OTHER, other)
        BREAK2ID(PREPEND, prepend)
        BREAK2ID(REGIONAL_INDICATOR, regional_indicator)
        BREAK2ID(SPACINGMARK, spacingmark)
        BREAK2ID(T, t)
        BREAK2ID(V, v)
        default:
                rb_u_raise(rb_eNotImpError, "unknown grapheme break: %d", value);
        }
}

/* Returns the grapheme break property value of the characters of the receiver.
 *
 * The possible break values are
 *
 * * :control
 * * :cr
 * * :extend
 * * :l
 * * :lf
 * * :lv
 * * :lvt
 * * :other
 * * :prepend
 * * :regional_indicator
 * * :spacingmark
 * * :t
 * * :v
 *
 * @raise [ArgumentError] If the string consists of more than one break type
 * @return [Symbol]
 * @see http://www.unicode.org/reports/tr29/
 *   Unicode Standard Annex #29: Unicode Text Segmentation */
VALUE
rb_u_string_grapheme_break(VALUE self)
{
        return _rb_u_string_property(self, "grapheme break", U_GRAPHEME_BREAK_OTHER,
                                     (int (*)(uint32_t))u_char_grapheme_break,
                                     (VALUE (*)(int))break_to_symbol);
}
