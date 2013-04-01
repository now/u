#include "rb_includes.h"

#define TYPE2ID(type, symbol) \
        case U_##type: { \
                static ID id_##symbol; \
                if (id_##symbol == 0) \
                        id_##symbol = rb_intern(#symbol); \
                return ID2SYM(id_##symbol); \
        }

static VALUE
type_to_symbol(UnicodeType type)
{
        switch (type) {
        TYPE2ID(OTHER_CONTROL, other_control)
        TYPE2ID(OTHER_FORMAT, other_format)
        TYPE2ID(OTHER_NOT_ASSIGNED, other_not_assigned)
        TYPE2ID(OTHER_PRIVATE_USE, other_private_use)
        TYPE2ID(OTHER_SURROGATE, other_surrogate)
        TYPE2ID(LETTER_LOWERCASE, letter_lowercase)
        TYPE2ID(LETTER_MODIFIER, letter_modifier)
        TYPE2ID(LETTER_OTHER, letter_other)
        TYPE2ID(LETTER_TITLECASE, letter_titlecase)
        TYPE2ID(LETTER_UPPERCASE, letter_uppercase)
        TYPE2ID(MARK_SPACING_COMBINING, mark_spacing_combining)
        TYPE2ID(MARK_ENCLOSING, mark_enclosing)
        TYPE2ID(MARK_NON_SPACING, mark_non_spacing)
        TYPE2ID(NUMBER_DECIMAL, number_decimal)
        TYPE2ID(NUMBER_LETTER, number_letter)
        TYPE2ID(NUMBER_OTHER, number_other)
        TYPE2ID(PUNCTUATION_CONNECTOR, punctuation_connector)
        TYPE2ID(PUNCTUATION_DASH, punctuation_dash)
        TYPE2ID(PUNCTUATION_CLOSE, punctuation_close)
        TYPE2ID(PUNCTUATION_FINAL_QUOTE, punctuation_final_quote)
        TYPE2ID(PUNCTUATION_INITIAL_QUOTE, punctuation_initial_quote)
        TYPE2ID(PUNCTUATION_OTHER, punctuation_other)
        TYPE2ID(PUNCTUATION_OPEN, punctuation_open)
        TYPE2ID(SYMBOL_CURRENCY, symbol_currency)
        TYPE2ID(SYMBOL_MODIFIER, symbol_modifier)
        TYPE2ID(SYMBOL_MATH, symbol_math)
        TYPE2ID(SYMBOL_OTHER, symbol_other)
        TYPE2ID(SEPARATOR_LINE, separator_line)
        TYPE2ID(SEPARATOR_PARAGRAPH, separator_paragraph)
        TYPE2ID(SEPARATOR_SPACE, separator_space)
        default:
                rb_u_raise(rb_eNotImpError, "unknown type: %d", type);
        }
}

/* Returns the general category of the characters of the receiver.
 *
 * The general category identifies what kind of symbol the character is.
 *
 * <table>
 *   <thead>
 *     <tr>
 *       <th>Category Major, minor</th>
 *       <th>Unicode Value</th>
 *       <th>Ruby Value</th>
 *     </tr>
 *   </thead>
 *   <tbody>
 *     <tr><td>Other, control</td><td>Cc</td><td>:other_control</td></tr>
 *     <tr><td>Other, format</td><td>Cf</td><td>:other_format</td></tr>
 *     <tr><td>Other, not assigned</td><td>Cn</td><td>:other_not_assigned</td></tr>
 *     <tr><td>Other, private use</td><td>Co</td><td>:other_private_use</td></tr>
 *     <tr><td>Other, surrogate</td><td>Cs</td><td>:other_surrogate</td></tr>
 *     <tr><td>Letter, lowercase</td><td>Ll</td><td>:letter_lowercase</td></tr>
 *     <tr><td>Letter, modifier</td><td>Lm</td><td>:letter_modifier</td></tr>
 *     <tr><td>Letter, other</td><td>Lo</td><td>:letter_other</td></tr>
 *     <tr><td>Letter, titlecase</td><td>Lt</td><td>:letter_titlecase</td></tr>
 *     <tr><td>Letter, uppercase</td><td>Lu</td><td>:letter_uppercase</td></tr>
 *     <tr><td>Mark, spacing combining</td><td>Mc</td><td>:mark_spacing_combining</td></tr>
 *     <tr><td>Mark, enclosing</td><td>Me</td><td>:mark_enclosing</td></tr>
 *     <tr><td>Mark, nonspacing</td><td>Mn</td><td>:mark_non_spacing</td></tr>
 *     <tr><td>Number, decimal digit</td><td>Nd</td><td>:number_decimal</td></tr>
 *     <tr><td>Number, letter</td><td>Nl</td><td>:number_letter</td></tr>
 *     <tr><td>Number, other</td><td>No</td><td>:number_other</td></tr>
 *     <tr><td>Punctuation, connector</td><td>Pc</td><td>:punctuation_connector</td></tr>
 *     <tr><td>Punctuation, dash</td><td>Pd</td><td>:punctuation_dash</td></tr>
 *     <tr><td>Punctuation, close</td><td>Pe</td><td>:punctuation_close</td></tr>
 *     <tr><td>Punctuation, final quote</td><td>Pf</td><td>:punctuation_final_quote</td></tr>
 *     <tr><td>Punctuation, initial quote</td><td>Pi</td><td>:punctuation_initial_quote</td></tr>
 *     <tr><td>Punctuation, other</td><td>Po</td><td>:punctuation_other</td></tr>
 *     <tr><td>Punctuation, open</td><td>Ps</td><td>:punctuation_open</td></tr>
 *     <tr><td>Symbol, currency</td><td>Sc</td><td>:symbol_currency</td></tr>
 *     <tr><td>Symbol, modifier</td><td>Sk</td><td>:symbol_modifier</td></tr>
 *     <tr><td>Symbol, math</td><td>Sm</td><td>:symbol_math</td></tr>
 *     <tr><td>Symbol, other</td><td>So</td><td>:symbol_other</td></tr>
 *     <tr><td>Separator, line</td><td>Zl</td><td>:separator_line</td></tr>
 *     <tr><td>Separator, paragraph</td><td>Zp</td><td>:separator_paragraph</td></tr>
 *     <tr><td>Separator, space</td><td>Zs</td><td>:separator_space</td></tr>
 *   </tbody>
 * </table>
 *
 * @raise [ArgumentError] If the receiver contains two characters belonging to
 *   different general categories
 * @raise [ArgumentError] If the receiver contains an incomplete UTF-8 sequence
 * @raise [ArgumentError] If the receiver contains an invalid UTF-8 sequence
 * @return [Symbol]
 * @see http://www.unicode.org/notes/tn36/
 *   Unicode Technical Note #36: A Categorization of Unicode Characters */
VALUE
rb_u_string_category(VALUE self)
{
        UnicodeType current = (UnicodeType)-1;

        const UString *string = RVAL2USTRING(self);

        const char *p = USTRING_STR(string);
        const char *end = USTRING_END(string);
        while (p < end) {
                UnicodeType type = u_char_type(u_aref_char_validated_n(p, end - p));

                if (current == (UnicodeType)-1)
                        current = type;
                else if (type != current)
                        rb_u_raise(rb_eArgError,
                                   "string consists of more than one type: :%s+, :%s",
                                   rb_id2name(SYM2ID(type_to_symbol(current))),
                                   rb_id2name(SYM2ID(type_to_symbol(type))));

                p = u_next(p);
        }

        return type_to_symbol(current);
}
