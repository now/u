#include "rb_includes.h"

#define TYPE2ID(type, symbol) \
        static ID id_##symbol; \
        if (id_##symbol == 0) \
                id_##symbol = rb_intern(#symbol);

static VALUE
type_to_symbol(UnicodeType type)
{
        TYPE2ID(U_CONTROL, control);
        TYPE2ID(U_FORMAT, format);
        TYPE2ID(U_UNASSIGNED, unassigned);
        TYPE2ID(U_PRIVATE_USE, private_use);
        TYPE2ID(U_SURROGATE, surrogate);
        TYPE2ID(U_LOWERCASE_LETTER, lowercase_letter);
        TYPE2ID(U_MODIFIER_LETTER, modifier_letter);
        TYPE2ID(U_OTHER_LETTER, other_letter);
        TYPE2ID(U_TITLECASE_LETTER, titlecase_letter);
        TYPE2ID(U_UPPERCASE_LETTER, uppercase_letter);
        TYPE2ID(U_SPACING_MARK, spacing_mark);
        TYPE2ID(U_ENCLOSING_MARK, enclosing_mark);
        TYPE2ID(U_NON_SPACING_MARK, non_spacing_mark);
        TYPE2ID(U_DECIMAL_NUMBER, decimal_number);
        TYPE2ID(U_LETTER_NUMBER, letter_number);
        TYPE2ID(U_OTHER_NUMBER, other_number);
        TYPE2ID(U_CONNECT_PUNCTUATION, connect_punctuation);
        TYPE2ID(U_DASH_PUNCTUATION, dash_punctuation);
        TYPE2ID(U_CLOSE_PUNCTUATION, close_punctuation);
        TYPE2ID(U_FINAL_PUNCTUATION, final_punctuation);
        TYPE2ID(U_INITIAL_PUNCTUATION, initial_punctuation);
        TYPE2ID(U_OTHER_PUNCTUATION, other_punctuation);
        TYPE2ID(U_OPEN_PUNCTUATION, open_punctuation);
        TYPE2ID(U_CURRENCY_SYMBOL, currency_symbol);
        TYPE2ID(U_MODIFIER_SYMBOL, modifier_symbol);
        TYPE2ID(U_MATH_SYMBOL, math_symbol);
        TYPE2ID(U_OTHER_SYMBOL, other_symbol);
        TYPE2ID(U_LINE_SEPARATOR, line_separator);
        TYPE2ID(U_PARAGRAPH_SEPARATOR, paragraph_separator);
        TYPE2ID(U_SPACE_SEPARATOR, space_separator);

        switch (type) {
        case U_CONTROL:
                return ID2SYM(id_control);
        case U_FORMAT:
                return ID2SYM(id_format);
        case U_UNASSIGNED:
                return ID2SYM(id_unassigned);
        case U_PRIVATE_USE:
                return ID2SYM(id_private_use);
        case U_SURROGATE:
                return ID2SYM(id_surrogate);
        case U_LOWERCASE_LETTER:
                return ID2SYM(id_lowercase_letter);
        case U_MODIFIER_LETTER:
                return ID2SYM(id_modifier_letter);
        case U_OTHER_LETTER:
                return ID2SYM(id_other_letter);
        case U_TITLECASE_LETTER:
                return ID2SYM(id_titlecase_letter);
        case U_UPPERCASE_LETTER:
                return ID2SYM(id_uppercase_letter);
        case U_SPACING_MARK:
                return ID2SYM(id_spacing_mark);
        case U_ENCLOSING_MARK:
                return ID2SYM(id_enclosing_mark);
        case U_NON_SPACING_MARK:
                return ID2SYM(id_non_spacing_mark);
        case U_DECIMAL_NUMBER:
                return ID2SYM(id_decimal_number);
        case U_LETTER_NUMBER:
                return ID2SYM(id_letter_number);
        case U_OTHER_NUMBER:
                return ID2SYM(id_other_number);
        case U_CONNECT_PUNCTUATION:
                return ID2SYM(id_connect_punctuation);
        case U_DASH_PUNCTUATION:
                return ID2SYM(id_dash_punctuation);
        case U_CLOSE_PUNCTUATION:
                return ID2SYM(id_close_punctuation);
        case U_FINAL_PUNCTUATION:
                return ID2SYM(id_final_punctuation);
        case U_INITIAL_PUNCTUATION:
                return ID2SYM(id_initial_punctuation);
        case U_OTHER_PUNCTUATION:
                return ID2SYM(id_other_punctuation);
        case U_OPEN_PUNCTUATION:
                return ID2SYM(id_open_punctuation);
        case U_CURRENCY_SYMBOL:
                return ID2SYM(id_currency_symbol);
        case U_MODIFIER_SYMBOL:
                return ID2SYM(id_modifier_symbol);
        case U_MATH_SYMBOL:
                return ID2SYM(id_math_symbol);
        case U_OTHER_SYMBOL:
                return ID2SYM(id_other_symbol);
        case U_LINE_SEPARATOR:
                return ID2SYM(id_line_separator);
        case U_PARAGRAPH_SEPARATOR:
                return ID2SYM(id_paragraph_separator);
        case U_SPACE_SEPARATOR:
                return ID2SYM(id_space_separator);
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
 *     <tr><td>Other, control</td><td>Cc</td><td>:control</td></tr>
 *     <tr><td>Other, format</td><td>Cf</td><td>:format</td></tr>
 *     <tr><td>Other, not assigned</td><td>Cn</td><td>:unassigned</td></tr>
 *     <tr><td>Other, private use</td><td>Co</td><td>:private_use</td></tr>
 *     <tr><td>Other, surrogate</td><td>Cs</td><td>:surrogate</td></tr>
 *     <tr><td>Letter, lowercase</td><td>Ll</td><td>:lowercase_letter</td></tr>
 *     <tr><td>Letter, modifier</td><td>Lm</td><td>:modifier_letter</td></tr>
 *     <tr><td>Letter, other</td><td>Lo</td><td>:other_letter</td></tr>
 *     <tr><td>Letter, titlecase</td><td>Lt</td><td>:titlecase_letter</td></tr>
 *     <tr><td>Letter, uppercase</td><td>Lu</td><td>:uppercase_letter</td></tr>
 *     <tr><td>Mark, spacing combining</td><td>Mc</td><td>:spacing_mark</td></tr>
 *     <tr><td>Mark, enclosing</td><td>Me</td><td>:enclosing_mark</td></tr>
 *     <tr><td>Mark, nonspacing</td><td>Mn</td><td>:non_spacing_mark</td></tr>
 *     <tr><td>Number, decimal digit</td><td>Nd</td><td>:decimal_number</td></tr>
 *     <tr><td>Number, letter</td><td>Nl</td><td>:letter_number</td></tr>
 *     <tr><td>Number, other</td><td>No</td><td>:other_number</td></tr>
 *     <tr><td>Punctuation, connector</td><td>Pc</td><td>:connect_punctuation</td></tr>
 *     <tr><td>Punctuation, dash</td><td>Pd</td><td>:dash_punctuation</td></tr>
 *     <tr><td>Punctuation, close</td><td>Pe</td><td>:close_punctuation</td></tr>
 *     <tr><td>Punctuation, final quote</td><td>Pf</td><td>:final_punctuation</td></tr>
 *     <tr><td>Punctuation, initial quote</td><td>Pi</td><td>:initial_punctuation</td></tr>
 *     <tr><td>Punctuation, other</td><td>Po</td><td>:other_punctuation</td></tr>
 *     <tr><td>Punctuation, open</td><td>Ps</td><td>:open_punctuation</td></tr>
 *     <tr><td>Symbol, currency</td><td>Sc</td><td>:currency_symbol</td></tr>
 *     <tr><td>Symbol, modifier</td><td>Sk</td><td>:modifier_symbol</td></tr>
 *     <tr><td>Symbol, math</td><td>Sm</td><td>:math_symbol</td></tr>
 *     <tr><td>Symbol, other</td><td>So</td><td>:other_symbol</td></tr>
 *     <tr><td>Separator, line</td><td>Zl</td><td>:line_separator</td></tr>
 *     <tr><td>Separator, paragraph</td><td>Zp</td><td>:paragraph_separator</td></tr>
 *     <tr><td>Separator, space</td><td>Zs</td><td>:space_separator</td></tr>
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
