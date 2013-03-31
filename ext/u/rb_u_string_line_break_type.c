#include "rb_includes.h"

#define TYPE2ID(type, symbol) \
        case U_LINE_BREAK_##type: { \
                static ID id_##symbol; \
                if (id_##symbol == 0) \
                        id_##symbol = rb_intern(#symbol); \
                return ID2SYM(id_##symbol); \
        }

static VALUE
break_type_to_symbol(UnicodeLineBreakType type)
{
        switch (type) {
        TYPE2ID(MANDATORY, mandatory)
        TYPE2ID(CARRIAGE_RETURN, carriage_return)
        TYPE2ID(LINE_FEED, line_feed)
        TYPE2ID(COMBINING_MARK, combining_mark)
        TYPE2ID(NEXT_LINE, next_line)
        TYPE2ID(SURROGATE, surrogate)
        TYPE2ID(WORD_JOINER, word_joiner)
        TYPE2ID(ZERO_WIDTH_SPACE, zero_width_space)
        TYPE2ID(NON_BREAKING_GLUE, non_breaking_glue)
        TYPE2ID(SPACE, space)
        TYPE2ID(BREAK_OPPORTUNITY_BEFORE_AND_AFTER, break_opportunity_before_and_after)
        TYPE2ID(BREAK_AFTER, break_after)
        TYPE2ID(BREAK_BEFORE, break_before)
        TYPE2ID(HYPHEN, hyphen)
        TYPE2ID(CONTINGENT_BREAK_OPPORTUNITY, contingent_break_opportunity)
        TYPE2ID(CLOSE_PUNCTUATION, close_punctuation)
        TYPE2ID(CLOSE_PARENTHESIS, close_parenthesis)
        TYPE2ID(EXCLAMATION_INTERROGATION, exclamation_interrogation)
        TYPE2ID(INSEPARABLE, inseparable)
        TYPE2ID(NONSTARTER, nonstarter)
        TYPE2ID(OPEN_PUNCTUATION, open_punctuation)
        TYPE2ID(QUOTATION, quotation)
        TYPE2ID(INFIX_NUMERIC_SEPARATOR, infix_numeric_separator)
        TYPE2ID(NUMERIC, numeric)
        TYPE2ID(POSTFIX_NUMERIC, postfix_numeric)
        TYPE2ID(PREFIX_NUMERIC, prefix_numeric)
        TYPE2ID(SYMBOLS_ALLOWING_BREAK_AFTER, symbols_allowing_break_after)
        TYPE2ID(AMBIGUOUS, ambiguous)
        TYPE2ID(ALPHABETIC, alphabetic)
        TYPE2ID(CONDITIONAL_JAPANESE_STARTER, conditional_japanese_starter)
        TYPE2ID(HANGUL_LV_SYLLABLE, hangul_lv_syllable)
        TYPE2ID(HANGUL_LVT_SYLLABLE, hangul_lvt_syllable)
        TYPE2ID(HEBREW_LETTER, hebrew_letter)
        TYPE2ID(IDEOGRAPHIC, ideographic)
        TYPE2ID(HANGUL_L_JAMO, hangul_l_jamo)
        TYPE2ID(HANGUL_V_JAMO, hangul_v_jamo)
        TYPE2ID(HANGUL_T_JAMO, hangul_t_jamo)
        TYPE2ID(REGIONAL_INDICATOR, regional_indicator)
        TYPE2ID(COMPLEX_CONTEXT_DEPENDENT, complex_context_dependent)
        TYPE2ID(UNKNOWN, unknown)
        default:
                rb_u_raise(rb_eNotImpError, "unknown break type: %d", type);
        }
}

/* Returns the line break type of the characters of the receiver.
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
 * @raise [ArgumentError] If the string consists of more than one break type
 * @return [Symbol]
 * @see http://unicode.org/reports/tr14/
 *   Unicode Standard Annex #14: Unicode Line Breaking Algorithm */
VALUE
rb_u_string_line_break_type(VALUE self)
{
        UnicodeLineBreakType current = U_LINE_BREAK_UNKNOWN;

        const UString *string = RVAL2USTRING(self);

        const char *p = USTRING_STR(string);
        const char *end = USTRING_END(string);
        while (p < end) {
                UnicodeLineBreakType type = unichar_line_break_type(u_aref_char_validated_n(p, end - p));

                if (current == U_LINE_BREAK_UNKNOWN)
                        current = type;
                else if (type != current)
                        rb_u_raise(rb_eArgError,
                                   "string consists of more than one line break type: :%s+, :%s",
                                   rb_id2name(SYM2ID(break_type_to_symbol(current))),
                                   rb_id2name(SYM2ID(break_type_to_symbol(type))));

                p = u_next(p);
        }

        return break_type_to_symbol(current);
}
