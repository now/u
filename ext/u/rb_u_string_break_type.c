#include "rb_includes.h"

#define BREAKTYPE2ID(type, symbol) \
        static ID id_##symbol; \
        if (id_##symbol == 0) \
                id_##symbol = rb_intern(#symbol);

static VALUE
break_type_to_symbol(UnicodeBreakType type)
{
	BREAKTYPE2ID(UNICODE_BREAK_MANDATORY, mandatory);
	BREAKTYPE2ID(UNICODE_BREAK_CARRIAGE_RETURN, carriage_return);
	BREAKTYPE2ID(UNICODE_BREAK_LINE_FEED, line_feed);
	BREAKTYPE2ID(UNICODE_BREAK_COMBINING_MARK, combining_mark);
	BREAKTYPE2ID(UNICODE_BREAK_SURROGATE, surrogate);
	BREAKTYPE2ID(UNICODE_BREAK_ZERO_WIDTH_SPACE, zero_width_space);
	BREAKTYPE2ID(UNICODE_BREAK_INSEPARABLE, inseparable);
	BREAKTYPE2ID(UNICODE_BREAK_NON_BREAKING_GLUE, non_breaking_glue);
	BREAKTYPE2ID(UNICODE_BREAK_CONTINGENT, contingent);
	BREAKTYPE2ID(UNICODE_BREAK_SPACE, space);
	BREAKTYPE2ID(UNICODE_BREAK_AFTER, after);
	BREAKTYPE2ID(UNICODE_BREAK_BEFORE, before);
	BREAKTYPE2ID(UNICODE_BREAK_BEFORE_AND_AFTER, before_and_after);
	BREAKTYPE2ID(UNICODE_BREAK_HYPHEN, hyphen);
	BREAKTYPE2ID(UNICODE_BREAK_NON_STARTER, non_starter);
	BREAKTYPE2ID(UNICODE_BREAK_OPEN_PUNCTUATION, open_punctuation);
	BREAKTYPE2ID(UNICODE_BREAK_CLOSE_PUNCTUATION, close_punctuation);
	BREAKTYPE2ID(UNICODE_BREAK_QUOTATION, quotation);
	BREAKTYPE2ID(UNICODE_BREAK_EXCLAMATION, exclamation);
	BREAKTYPE2ID(UNICODE_BREAK_IDEOGRAPHIC, ideographic);
	BREAKTYPE2ID(UNICODE_BREAK_NUMERIC, numeric);
	BREAKTYPE2ID(UNICODE_BREAK_INFIX_SEPARATOR, infix_separator);
	BREAKTYPE2ID(UNICODE_BREAK_SYMBOL, symbol);
	BREAKTYPE2ID(UNICODE_BREAK_ALPHABETIC, alphabetic);
	BREAKTYPE2ID(UNICODE_BREAK_PREFIX, prefix);
	BREAKTYPE2ID(UNICODE_BREAK_POSTFIX, postfix);
	BREAKTYPE2ID(UNICODE_BREAK_COMPLEX_CONTEXT, complex_context);
	BREAKTYPE2ID(UNICODE_BREAK_AMBIGUOUS, ambiguous);
	BREAKTYPE2ID(UNICODE_BREAK_UNKNOWN, unknown);
	BREAKTYPE2ID(UNICODE_BREAK_NEXT_LINE, next_line);
	BREAKTYPE2ID(UNICODE_BREAK_WORD_JOINER, word_joiner);
        BREAKTYPE2ID(UNICODE_BREAK_HANGUL_L_JAMO, hangul_l_jamo);
        BREAKTYPE2ID(UNICODE_BREAK_HANGUL_V_JAMO, hangul_v_jamo);
        BREAKTYPE2ID(UNICODE_BREAK_HANGUL_T_JAMO, hangul_t_jamo);
        BREAKTYPE2ID(UNICODE_BREAK_HANGUL_LV_SYLLABLE, hangul_lv_syllable);
        BREAKTYPE2ID(UNICODE_BREAK_HANGUL_LVT_SYLLABLE, hangul_lvt_syllable);
        BREAKTYPE2ID(UNICODE_BREAK_CLOSE_PARENTHESIS, close_parenthesis);

        switch (type) {
	case UNICODE_BREAK_MANDATORY:
		return ID2SYM(id_mandatory);
	case UNICODE_BREAK_CARRIAGE_RETURN:
		return ID2SYM(id_carriage_return);
	case UNICODE_BREAK_LINE_FEED:
		return ID2SYM(id_line_feed);
	case UNICODE_BREAK_COMBINING_MARK:
		return ID2SYM(id_combining_mark);
	case UNICODE_BREAK_SURROGATE:
		return ID2SYM(id_surrogate);
	case UNICODE_BREAK_ZERO_WIDTH_SPACE:
		return ID2SYM(id_space);
	case UNICODE_BREAK_INSEPARABLE:
		return ID2SYM(id_inseparable);
	case UNICODE_BREAK_NON_BREAKING_GLUE:
		return ID2SYM(id_non_breaking_glue);
	case UNICODE_BREAK_CONTINGENT:
		return ID2SYM(id_contingent);
	case UNICODE_BREAK_SPACE:
		return ID2SYM(id_space);
	case UNICODE_BREAK_AFTER:
		return ID2SYM(id_after);
	case UNICODE_BREAK_BEFORE:
		return ID2SYM(id_before);
	case UNICODE_BREAK_BEFORE_AND_AFTER:
		return ID2SYM(id_after);
	case UNICODE_BREAK_HYPHEN:
		return ID2SYM(id_hyphen);
	case UNICODE_BREAK_NON_STARTER:
		return ID2SYM(id_non_starter);
	case UNICODE_BREAK_OPEN_PUNCTUATION:
		return ID2SYM(id_open_punctuation);
	case UNICODE_BREAK_CLOSE_PUNCTUATION:
		return ID2SYM(id_close_punctuation);
	case UNICODE_BREAK_QUOTATION:
		return ID2SYM(id_quotation);
	case UNICODE_BREAK_EXCLAMATION:
		return ID2SYM(id_exclamation);
	case UNICODE_BREAK_IDEOGRAPHIC:
		return ID2SYM(id_ideographic);
	case UNICODE_BREAK_NUMERIC:
		return ID2SYM(id_numeric);
	case UNICODE_BREAK_INFIX_SEPARATOR:
		return ID2SYM(id_infix_separator);
	case UNICODE_BREAK_SYMBOL:
		return ID2SYM(id_symbol);
	case UNICODE_BREAK_ALPHABETIC:
		return ID2SYM(id_alphabetic);
	case UNICODE_BREAK_PREFIX:
		return ID2SYM(id_prefix);
	case UNICODE_BREAK_POSTFIX:
		return ID2SYM(id_postfix);
	case UNICODE_BREAK_COMPLEX_CONTEXT:
		return ID2SYM(id_complex_context);
	case UNICODE_BREAK_AMBIGUOUS:
		return ID2SYM(id_ambiguous);
	case UNICODE_BREAK_UNKNOWN:
		return ID2SYM(id_unknown);
	case UNICODE_BREAK_NEXT_LINE:
		return ID2SYM(id_next_line);
	case UNICODE_BREAK_WORD_JOINER:
		return ID2SYM(id_word_joiner);
        case UNICODE_BREAK_HANGUL_L_JAMO:
		return ID2SYM(id_hangul_l_jamo);
        case UNICODE_BREAK_HANGUL_V_JAMO:
		return ID2SYM(id_hangul_v_jamo);
        case UNICODE_BREAK_HANGUL_T_JAMO:
		return ID2SYM(id_hangul_t_jamo);
        case UNICODE_BREAK_HANGUL_LV_SYLLABLE:
		return ID2SYM(id_hangul_lv_syllable);
        case UNICODE_BREAK_HANGUL_LVT_SYLLABLE:
		return ID2SYM(id_hangul_lvt_syllable);
        case UNICODE_BREAK_CLOSE_PARENTHESIS:
		return ID2SYM(id_close_parenthesis);
        default:
                rb_raise(rb_eNotImpError, "unknown break type: %d", type);
        }
}

/* Determines the break type of the characters of this {U::String}.
 *
 * The possible break types are
 *
 * * :mandatory
 * * :carriage_return
 * * :line_feed
 * * :combining_mark
 * * :surrogate
 * * :zero_width_space
 * * :inseparable
 * * :non_breaking_glue
 * * :contingent
 * * :space
 * * :after
 * * :before
 * * :before_and_after
 * * :hyphen
 * * :non_starter
 * * :open_punctuation
 * * :close_punctuation
 * * :quotation
 * * :exclamation
 * * :ideographic
 * * :numeric
 * * :infix_separator
 * * :symbol
 * * :alphabetic
 * * :prefix
 * * :postfix
 * * :complex_context
 * * :ambiguous
 * * :unknown
 * * :next_line
 * * :word_joiner
 * * :hangul_l_jamo
 * * :hangul_v_jamo
 * * :hangul_t_jamo
 * * :hangul_lv_syllable
 * * :hangul_lvt_syllable
 * * :close_parenthesis
 *
 * For more information on the Unicode line-breaking algorithm, see Unicode
 * Standard Annex #14, http://unicode.org/reports/tr14/.
 *
 * @raise [ArgumentError] The string consists of more than one break type
 * @return [Symbol] The break type */
VALUE
rb_u_string_break_type(VALUE self)
{
        UnicodeBreakType current = UNICODE_BREAK_UNKNOWN;

        const UString *string = RVAL2USTRING(self);

        const char *p = USTRING_STR(string);
        const char *end = USTRING_END(string);
        while (p < end) {
                UnicodeBreakType type = unichar_break_type(u_aref_char_validated_n(p, end - p));

                if (current == UNICODE_BREAK_UNKNOWN)
                        current = type;
                else if (type != current)
                        rb_raise(rb_eArgError,
                                 "string consists of more than one break type: :%s+, :%s",
                                 rb_id2name(SYM2ID(break_type_to_symbol(current))),
                                 rb_id2name(SYM2ID(break_type_to_symbol(type))));

                p = u_next(p);
        }

        return break_type_to_symbol(current);
}
