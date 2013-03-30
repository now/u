#include "rb_includes.h"

#define BREAKTYPE2ID(type, symbol) \
        static ID id_##symbol; \
        if (id_##symbol == 0) \
                id_##symbol = rb_intern(#symbol);

static VALUE
break_type_to_symbol(UnicodeWordBreakType type)
{
	BREAKTYPE2ID(U_WORD_BREAK_ALETTER, aletter);
	BREAKTYPE2ID(U_WORD_BREAK_CR, cr);
	BREAKTYPE2ID(U_WORD_BREAK_EXTEND, extend);
	BREAKTYPE2ID(U_WORD_BREAK_EXTENDNUMLET, extendnumlet);
	BREAKTYPE2ID(U_WORD_BREAK_FORMAT, format);
	BREAKTYPE2ID(U_WORD_BREAK_KATAKANA, katakana);
	BREAKTYPE2ID(U_WORD_BREAK_LF, lf);
	BREAKTYPE2ID(U_WORD_BREAK_MIDLETTER, midletter);
	BREAKTYPE2ID(U_WORD_BREAK_MIDNUM, midnum);
	BREAKTYPE2ID(U_WORD_BREAK_MIDNUMLET, midnumlet);
	BREAKTYPE2ID(U_WORD_BREAK_NEWLINE, newline);
	BREAKTYPE2ID(U_WORD_BREAK_NUMERIC, numeric);
	BREAKTYPE2ID(U_WORD_BREAK_OTHER, other);
	BREAKTYPE2ID(U_WORD_BREAK_REGIONAL_INDICATOR, regional_indicator);

        switch (type) {
	case U_WORD_BREAK_ALETTER:
		return ID2SYM(id_aletter);
	case U_WORD_BREAK_CR:
		return ID2SYM(id_cr);
	case U_WORD_BREAK_EXTEND:
		return ID2SYM(id_extend);
	case U_WORD_BREAK_EXTENDNUMLET:
		return ID2SYM(id_extendnumlet);
	case U_WORD_BREAK_FORMAT:
		return ID2SYM(id_format);
	case U_WORD_BREAK_KATAKANA:
		return ID2SYM(id_katakana);
	case U_WORD_BREAK_LF:
		return ID2SYM(id_lf);
	case U_WORD_BREAK_MIDLETTER:
		return ID2SYM(id_midletter);
	case U_WORD_BREAK_MIDNUM:
		return ID2SYM(id_midnum);
	case U_WORD_BREAK_MIDNUMLET:
		return ID2SYM(id_midnumlet);
	case U_WORD_BREAK_NEWLINE:
		return ID2SYM(id_newline);
	case U_WORD_BREAK_NUMERIC:
		return ID2SYM(id_numeric);
	case U_WORD_BREAK_OTHER:
		return ID2SYM(id_other);
	case U_WORD_BREAK_REGIONAL_INDICATOR:
		return ID2SYM(id_regional_indicator);
        default:
                rb_u_raise(rb_eNotImpError, "unknown break type: %d", type);
        }
}

/* Returns the word break type of the characters of the receiver.
 *
 * The possible word break types are
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
rb_u_string_word_break_type(VALUE self)
{
        const UString *string = RVAL2USTRING(self);
        const char *p = USTRING_STR(string);
        const char *end = USTRING_END(string);
        UnicodeWordBreakType current = unichar_word_break_type(u_aref_char_validated_n(p, end - p));
        p = u_next(p);
        while (p < end) {
                UnicodeWordBreakType type = unichar_word_break_type(u_aref_char_validated_n(p, end - p));
                if (type != current)
                        rb_u_raise(rb_eArgError,
                                   "string consists of more than one word break type: :%s+, :%s",
                                   rb_id2name(SYM2ID(break_type_to_symbol(current))),
                                   rb_id2name(SYM2ID(break_type_to_symbol(type))));
                p = u_next(p);
        }
        return break_type_to_symbol(current);
}
