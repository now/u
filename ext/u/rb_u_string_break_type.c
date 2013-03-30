#include "rb_includes.h"

#define BREAKTYPE2ID(type, symbol) \
        static ID id_##symbol; \
        if (id_##symbol == 0) \
                id_##symbol = rb_intern(#symbol);

static VALUE
break_type_to_symbol(UnicodeBreakType type)
{
	BREAKTYPE2ID(U_BREAK_MANDATORY, mandatory);
	BREAKTYPE2ID(U_BREAK_CARRIAGE_RETURN, carriage_return);
	BREAKTYPE2ID(U_BREAK_LINE_FEED, line_feed);
	BREAKTYPE2ID(U_BREAK_COMBINING_MARK, combining_mark);
	BREAKTYPE2ID(U_BREAK_SURROGATE, surrogate);
	BREAKTYPE2ID(U_BREAK_ZERO_WIDTH_SPACE, zero_width_space);
	BREAKTYPE2ID(U_BREAK_INSEPARABLE, inseparable);
	BREAKTYPE2ID(U_BREAK_NON_BREAKING_GLUE, non_breaking_glue);
	BREAKTYPE2ID(U_BREAK_CONTINGENT, contingent);
	BREAKTYPE2ID(U_BREAK_SPACE, space);
	BREAKTYPE2ID(U_BREAK_AFTER, after);
	BREAKTYPE2ID(U_BREAK_BEFORE, before);
	BREAKTYPE2ID(U_BREAK_BEFORE_AND_AFTER, before_and_after);
	BREAKTYPE2ID(U_BREAK_HYPHEN, hyphen);
	BREAKTYPE2ID(U_BREAK_NON_STARTER, non_starter);
	BREAKTYPE2ID(U_BREAK_OPEN_PUNCTUATION, open_punctuation);
	BREAKTYPE2ID(U_BREAK_CLOSE_PUNCTUATION, close_punctuation);
	BREAKTYPE2ID(U_BREAK_QUOTATION, quotation);
	BREAKTYPE2ID(U_BREAK_EXCLAMATION, exclamation);
	BREAKTYPE2ID(U_BREAK_IDEOGRAPHIC, ideographic);
	BREAKTYPE2ID(U_BREAK_NUMERIC, numeric);
	BREAKTYPE2ID(U_BREAK_INFIX_SEPARATOR, infix_separator);
	BREAKTYPE2ID(U_BREAK_SYMBOL, symbol);
	BREAKTYPE2ID(U_BREAK_ALPHABETIC, alphabetic);
	BREAKTYPE2ID(U_BREAK_PREFIX, prefix);
	BREAKTYPE2ID(U_BREAK_POSTFIX, postfix);
	BREAKTYPE2ID(U_BREAK_COMPLEX_CONTEXT, complex_context);
	BREAKTYPE2ID(U_BREAK_AMBIGUOUS, ambiguous);
	BREAKTYPE2ID(U_BREAK_UNKNOWN, unknown);
	BREAKTYPE2ID(U_BREAK_NEXT_LINE, next_line);
	BREAKTYPE2ID(U_BREAK_WORD_JOINER, word_joiner);
        BREAKTYPE2ID(U_BREAK_HANGUL_L_JAMO, hangul_l_jamo);
        BREAKTYPE2ID(U_BREAK_HANGUL_V_JAMO, hangul_v_jamo);
        BREAKTYPE2ID(U_BREAK_HANGUL_T_JAMO, hangul_t_jamo);
        BREAKTYPE2ID(U_BREAK_HANGUL_LV_SYLLABLE, hangul_lv_syllable);
        BREAKTYPE2ID(U_BREAK_HANGUL_LVT_SYLLABLE, hangul_lvt_syllable);
        BREAKTYPE2ID(U_BREAK_CLOSE_PARENTHESIS, close_parenthesis);
        BREAKTYPE2ID(U_BREAK_HEBREW_LETTER, hebrew_letter);
        BREAKTYPE2ID(U_BREAK_CONDITIONAL_JAPANESE_STARTER, conditional_japanese_starter);
        BREAKTYPE2ID(U_BREAK_REGIONAL_INDICATOR, regional_indicator);

        switch (type) {
	case U_BREAK_MANDATORY:
		return ID2SYM(id_mandatory);
	case U_BREAK_CARRIAGE_RETURN:
		return ID2SYM(id_carriage_return);
	case U_BREAK_LINE_FEED:
		return ID2SYM(id_line_feed);
	case U_BREAK_COMBINING_MARK:
		return ID2SYM(id_combining_mark);
	case U_BREAK_SURROGATE:
		return ID2SYM(id_surrogate);
	case U_BREAK_ZERO_WIDTH_SPACE:
		return ID2SYM(id_space);
	case U_BREAK_INSEPARABLE:
		return ID2SYM(id_inseparable);
	case U_BREAK_NON_BREAKING_GLUE:
		return ID2SYM(id_non_breaking_glue);
	case U_BREAK_CONTINGENT:
		return ID2SYM(id_contingent);
	case U_BREAK_SPACE:
		return ID2SYM(id_space);
	case U_BREAK_AFTER:
		return ID2SYM(id_after);
	case U_BREAK_BEFORE:
		return ID2SYM(id_before);
	case U_BREAK_BEFORE_AND_AFTER:
		return ID2SYM(id_after);
	case U_BREAK_HYPHEN:
		return ID2SYM(id_hyphen);
	case U_BREAK_NON_STARTER:
		return ID2SYM(id_non_starter);
	case U_BREAK_OPEN_PUNCTUATION:
		return ID2SYM(id_open_punctuation);
	case U_BREAK_CLOSE_PUNCTUATION:
		return ID2SYM(id_close_punctuation);
	case U_BREAK_QUOTATION:
		return ID2SYM(id_quotation);
	case U_BREAK_EXCLAMATION:
		return ID2SYM(id_exclamation);
	case U_BREAK_IDEOGRAPHIC:
		return ID2SYM(id_ideographic);
	case U_BREAK_NUMERIC:
		return ID2SYM(id_numeric);
	case U_BREAK_INFIX_SEPARATOR:
		return ID2SYM(id_infix_separator);
	case U_BREAK_SYMBOL:
		return ID2SYM(id_symbol);
	case U_BREAK_ALPHABETIC:
		return ID2SYM(id_alphabetic);
	case U_BREAK_PREFIX:
		return ID2SYM(id_prefix);
	case U_BREAK_POSTFIX:
		return ID2SYM(id_postfix);
	case U_BREAK_COMPLEX_CONTEXT:
		return ID2SYM(id_complex_context);
	case U_BREAK_AMBIGUOUS:
		return ID2SYM(id_ambiguous);
	case U_BREAK_UNKNOWN:
		return ID2SYM(id_unknown);
	case U_BREAK_NEXT_LINE:
		return ID2SYM(id_next_line);
	case U_BREAK_WORD_JOINER:
		return ID2SYM(id_word_joiner);
        case U_BREAK_HANGUL_L_JAMO:
		return ID2SYM(id_hangul_l_jamo);
        case U_BREAK_HANGUL_V_JAMO:
		return ID2SYM(id_hangul_v_jamo);
        case U_BREAK_HANGUL_T_JAMO:
		return ID2SYM(id_hangul_t_jamo);
        case U_BREAK_HANGUL_LV_SYLLABLE:
		return ID2SYM(id_hangul_lv_syllable);
        case U_BREAK_HANGUL_LVT_SYLLABLE:
		return ID2SYM(id_hangul_lvt_syllable);
        case U_BREAK_CLOSE_PARENTHESIS:
		return ID2SYM(id_close_parenthesis);
        case U_BREAK_HEBREW_LETTER:
                return ID2SYM(id_hebrew_letter);
        case U_BREAK_CONDITIONAL_JAPANESE_STARTER:
                return ID2SYM(id_conditional_japanese_starter);
        case U_BREAK_REGIONAL_INDICATOR:
                return ID2SYM(id_regional_indicator);
        default:
                rb_u_raise(rb_eNotImpError, "unknown break type: %d", type);
        }
}

/* Returns the break type of the characters of the receiver.
 *
 * The possible break types are
 *
 * * :after
 * * :alphabetic
 * * :ambiguous
 * * :before
 * * :before_and_after
 * * :carriage_return
 * * :close_parenthesis
 * * :close_punctuation
 * * :combining_mark
 * * :complex_context
 * * :conditional_japanese_starter
 * * :contingent
 * * :exclamation
 * * :hangul_l_jamo
 * * :hangul_lv_syllable
 * * :hangul_lvt_syllable
 * * :hangul_t_jamo
 * * :hangul_v_jamo
 * * :hebrew_letter
 * * :hyphen
 * * :ideographic
 * * :infix_separator
 * * :inseparable
 * * :line_feed
 * * :mandatory
 * * :next_line
 * * :non_breaking_glue
 * * :non_starter
 * * :numeric
 * * :open_punctuation
 * * :postfix
 * * :prefix
 * * :quotation
 * * :regional_indicator
 * * :space
 * * :surrogate
 * * :symbol
 * * :unknown
 * * :word_joiner
 * * :zero_width_space
 *
 * For more information on the Unicode line-breaking algorithm, see Unicode
 * Standard Annex #14, http://unicode.org/reports/tr14/.
 *
 * @raise [ArgumentError] If the string consists of more than one break type
 * @return [Symbol] */
VALUE
rb_u_string_break_type(VALUE self)
{
        UnicodeBreakType current = U_BREAK_UNKNOWN;

        const UString *string = RVAL2USTRING(self);

        const char *p = USTRING_STR(string);
        const char *end = USTRING_END(string);
        while (p < end) {
                UnicodeBreakType type = unichar_break_type(u_aref_char_validated_n(p, end - p));

                if (current == U_BREAK_UNKNOWN)
                        current = type;
                else if (type != current)
                        rb_u_raise(rb_eArgError,
                                   "string consists of more than one break type: :%s+, :%s",
                                   rb_id2name(SYM2ID(break_type_to_symbol(current))),
                                   rb_id2name(SYM2ID(break_type_to_symbol(type))));

                p = u_next(p);
        }

        return break_type_to_symbol(current);
}
