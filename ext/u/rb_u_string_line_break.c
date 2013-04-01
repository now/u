#include "rb_includes.h"

#define BREAK2ID(value, symbol) \
        case U_LINE_BREAK_##value: { \
                static ID id_##symbol; \
                if (id_##symbol == 0) \
                        id_##symbol = rb_intern(#symbol); \
                return ID2SYM(id_##symbol); \
        }

static VALUE
break_to_symbol(enum u_line_break value)
{
        switch (value) {
        BREAK2ID(MANDATORY, mandatory)
        BREAK2ID(CARRIAGE_RETURN, carriage_return)
        BREAK2ID(LINE_FEED, line_feed)
        BREAK2ID(COMBINING_MARK, combining_mark)
        BREAK2ID(NEXT_LINE, next_line)
        BREAK2ID(SURROGATE, surrogate)
        BREAK2ID(WORD_JOINER, word_joiner)
        BREAK2ID(ZERO_WIDTH_SPACE, zero_width_space)
        BREAK2ID(NON_BREAKING_GLUE, non_breaking_glue)
        BREAK2ID(SPACE, space)
        BREAK2ID(BREAK_OPPORTUNITY_BEFORE_AND_AFTER, break_opportunity_before_and_after)
        BREAK2ID(BREAK_AFTER, break_after)
        BREAK2ID(BREAK_BEFORE, break_before)
        BREAK2ID(HYPHEN, hyphen)
        BREAK2ID(CONTINGENT_BREAK_OPPORTUNITY, contingent_break_opportunity)
        BREAK2ID(CLOSE_PUNCTUATION, close_punctuation)
        BREAK2ID(CLOSE_PARENTHESIS, close_parenthesis)
        BREAK2ID(EXCLAMATION_INTERROGATION, exclamation_interrogation)
        BREAK2ID(INSEPARABLE, inseparable)
        BREAK2ID(NONSTARTER, nonstarter)
        BREAK2ID(OPEN_PUNCTUATION, open_punctuation)
        BREAK2ID(QUOTATION, quotation)
        BREAK2ID(INFIX_NUMERIC_SEPARATOR, infix_numeric_separator)
        BREAK2ID(NUMERIC, numeric)
        BREAK2ID(POSTFIX_NUMERIC, postfix_numeric)
        BREAK2ID(PREFIX_NUMERIC, prefix_numeric)
        BREAK2ID(SYMBOLS_ALLOWING_BREAK_AFTER, symbols_allowing_break_after)
        BREAK2ID(AMBIGUOUS, ambiguous)
        BREAK2ID(ALPHABETIC, alphabetic)
        BREAK2ID(CONDITIONAL_JAPANESE_STARTER, conditional_japanese_starter)
        BREAK2ID(HANGUL_LV_SYLLABLE, hangul_lv_syllable)
        BREAK2ID(HANGUL_LVT_SYLLABLE, hangul_lvt_syllable)
        BREAK2ID(HEBREW_LETTER, hebrew_letter)
        BREAK2ID(IDEOGRAPHIC, ideographic)
        BREAK2ID(HANGUL_L_JAMO, hangul_l_jamo)
        BREAK2ID(HANGUL_V_JAMO, hangul_v_jamo)
        BREAK2ID(HANGUL_T_JAMO, hangul_t_jamo)
        BREAK2ID(REGIONAL_INDICATOR, regional_indicator)
        BREAK2ID(COMPLEX_CONTEXT_DEPENDENT, complex_context_dependent)
        BREAK2ID(UNKNOWN, unknown)
        default:
                rb_u_raise(rb_eNotImpError, "unknown line break: %d", value);
        }
}

/* Returns the line break property value of the characters of the receiver.
 *
 * The possible break values are
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
rb_u_string_line_break(VALUE self)
{
        return _rb_u_string_property(self, "line break", U_LINE_BREAK_UNKNOWN,
                                     (int (*)(uint32_t))u_char_line_break,
                                     (VALUE (*)(int))break_to_symbol);
}
