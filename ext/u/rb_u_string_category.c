#include "rb_includes.h"

#define TYPE2ID(type, symbol) \
        static ID id_##symbol; \
        if (id_##symbol == 0) \
                id_##symbol = rb_intern(#symbol);

static VALUE
type_to_symbol(UnicodeType type)
{
        TYPE2ID(U_OTHER_CONTROL, other_control);
        TYPE2ID(U_OTHER_FORMAT, other_format);
        TYPE2ID(U_OTHER_NOT_ASSIGNED, other_not_assigned);
        TYPE2ID(U_OTHER_PRIVATE_USE, other_private_use);
        TYPE2ID(U_OTHER_SURROGATE, other_surrogate);
        TYPE2ID(U_LETTER_LOWERCASE, letter_lowercase);
        TYPE2ID(U_LETTER_MODIFIER, letter_modifier);
        TYPE2ID(U_LETTER_OTHER, letter_other);
        TYPE2ID(U_LETTER_TITLECASE, letter_titlecase);
        TYPE2ID(U_LETTER_UPPERCASE, letter_uppercase);
        TYPE2ID(U_MARK_SPACING_COMBINING, mark_spacing_combining);
        TYPE2ID(U_MARK_ENCLOSING, mark_enclosing);
        TYPE2ID(U_MARK_NON_SPACING, mark_non_spacing);
        TYPE2ID(U_NUMBER_DECIMAL, number_decimal);
        TYPE2ID(U_NUMBER_LETTER, number_letter);
        TYPE2ID(U_NUMBER_OTHER, number_other);
        TYPE2ID(U_PUNCTUATION_CONNECTOR, punctuation_connector);
        TYPE2ID(U_PUNCTUATION_DASH, punctuation_dash);
        TYPE2ID(U_PUNCTUATION_CLOSE, punctuation_close);
        TYPE2ID(U_PUNCTUATION_FINAL_QUOTE, punctuation_final_quote);
        TYPE2ID(U_PUNCTUATION_INITIAL_QUOTE, punctuation_initial_quote);
        TYPE2ID(U_PUNCTUATION_OTHER, punctuation_other);
        TYPE2ID(U_PUNCTUATION_OPEN, punctuation_open);
        TYPE2ID(U_SYMBOL_CURRENCY, symbol_currency);
        TYPE2ID(U_SYMBOL_MODIFIER, symbol_modifier);
        TYPE2ID(U_SYMBOL_MATH, symbol_math);
        TYPE2ID(U_SYMBOL_OTHER, symbol_other);
        TYPE2ID(U_SEPARATOR_LINE, separator_line);
        TYPE2ID(U_SEPARATOR_PARAGRAPH, separator_paragraph);
        TYPE2ID(U_SEPARATOR_SPACE, separator_space);

        switch (type) {
        case U_OTHER_CONTROL:
                return ID2SYM(id_other_control);
        case U_OTHER_FORMAT:
                return ID2SYM(id_other_format);
        case U_OTHER_NOT_ASSIGNED:
                return ID2SYM(id_other_not_assigned);
        case U_OTHER_PRIVATE_USE:
                return ID2SYM(id_other_private_use);
        case U_OTHER_SURROGATE:
                return ID2SYM(id_other_surrogate);
        case U_LETTER_LOWERCASE:
                return ID2SYM(id_letter_lowercase);
        case U_LETTER_MODIFIER:
                return ID2SYM(id_letter_modifier);
        case U_LETTER_OTHER:
                return ID2SYM(id_letter_other);
        case U_LETTER_TITLECASE:
                return ID2SYM(id_letter_titlecase);
        case U_LETTER_UPPERCASE:
                return ID2SYM(id_letter_uppercase);
        case U_MARK_SPACING_COMBINING:
                return ID2SYM(id_mark_spacing_combining);
        case U_MARK_ENCLOSING:
                return ID2SYM(id_mark_enclosing);
        case U_MARK_NON_SPACING:
                return ID2SYM(id_mark_non_spacing);
        case U_NUMBER_DECIMAL:
                return ID2SYM(id_number_decimal);
        case U_NUMBER_LETTER:
                return ID2SYM(id_number_letter);
        case U_NUMBER_OTHER:
                return ID2SYM(id_number_other);
        case U_PUNCTUATION_CONNECTOR:
                return ID2SYM(id_punctuation_connector);
        case U_PUNCTUATION_DASH:
                return ID2SYM(id_punctuation_dash);
        case U_PUNCTUATION_CLOSE:
                return ID2SYM(id_punctuation_close);
        case U_PUNCTUATION_FINAL_QUOTE:
                return ID2SYM(id_punctuation_final_quote);
        case U_PUNCTUATION_INITIAL_QUOTE:
                return ID2SYM(id_punctuation_initial_quote);
        case U_PUNCTUATION_OTHER:
                return ID2SYM(id_punctuation_other);
        case U_PUNCTUATION_OPEN:
                return ID2SYM(id_punctuation_open);
        case U_SYMBOL_CURRENCY:
                return ID2SYM(id_symbol_currency);
        case U_SYMBOL_MODIFIER:
                return ID2SYM(id_symbol_modifier);
        case U_SYMBOL_MATH:
                return ID2SYM(id_symbol_math);
        case U_SYMBOL_OTHER:
                return ID2SYM(id_symbol_other);
        case U_SEPARATOR_LINE:
                return ID2SYM(id_separator_line);
        case U_SEPARATOR_PARAGRAPH:
                return ID2SYM(id_separator_paragraph);
        case U_SEPARATOR_SPACE:
                return ID2SYM(id_separator_space);
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
                UnicodeType type = unichar_type(u_aref_char_validated_n(p, end - p));

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
