#include "rb_includes.h"

#define BREAK2ID(value, symbol) \
        case U_WORD_BREAK_##value: { \
                static ID id_##symbol; \
                if (id_##symbol == 0) \
                        id_##symbol = rb_intern(#symbol); \
                return ID2SYM(id_##symbol); \
        }

static VALUE
break_to_symbol(UnicodeWordBreak value)
{
        switch (value) {
	BREAK2ID(ALETTER, aletter);
	BREAK2ID(CR, cr);
	BREAK2ID(EXTEND, extend);
	BREAK2ID(EXTENDNUMLET, extendnumlet);
	BREAK2ID(FORMAT, format);
	BREAK2ID(KATAKANA, katakana);
	BREAK2ID(LF, lf);
	BREAK2ID(MIDLETTER, midletter);
	BREAK2ID(MIDNUM, midnum);
	BREAK2ID(MIDNUMLET, midnumlet);
	BREAK2ID(NEWLINE, newline);
	BREAK2ID(NUMERIC, numeric);
	BREAK2ID(OTHER, other);
	BREAK2ID(REGIONAL_INDICATOR, regional_indicator);
        default:
                rb_u_raise(rb_eNotImpError, "unknown word break value: %d", value);
        }
}

/* Returns the word break property value of the characters of the receiver.
 *
 * The possible word break values are
 *
 * * :aletter
 * * :cr
 * * :extend
 * * :extendnumlet
 * * :format
 * * :katakana
 * * :lf
 * * :midletter
 * * :midnum
 * * :midnumlet
 * * :newline
 * * :numeric
 * * :other
 * * :regional_indicator
 *
 * @raise [ArgumentError] If the string consists of more than one break type
 * @return [Symbol]
 * @see http://www.unicode.org/reports/tr29/
 *   Unicode Standard Annex #29: Unicode Text Segmentation */
VALUE
rb_u_string_word_break(VALUE self)
{
        return _rb_u_string_property(self, "word break", U_WORD_BREAK_OTHER,
                                     (int (*)(uint32_t))u_char_word_break,
                                     (VALUE (*)(int))break_to_symbol);
}
