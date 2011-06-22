#include "rb_includes.h"

#define TYPE2ID(type, symbol) \
        static ID id_##symbol; \
        if (id_##symbol == 0) \
                id_##symbol = rb_intern(#symbol);

static VALUE
type_to_symbol(UnicodeType type)
{
        TYPE2ID(UNICODE_CONTROL, control);
        TYPE2ID(UNICODE_FORMAT, format);
        TYPE2ID(UNICODE_UNASSIGNED, unassigned);
        TYPE2ID(UNICODE_PRIVATE_USE, private_use);
        TYPE2ID(UNICODE_SURROGATE, surrogate);
        TYPE2ID(UNICODE_LOWERCASE_LETTER, lowercase_letter);
        TYPE2ID(UNICODE_MODIFIER_LETTER, modifier_letter);
        TYPE2ID(UNICODE_OTHER_LETTER, other_letter);
        TYPE2ID(UNICODE_TITLECASE_LETTER, titlecase_letter);
        TYPE2ID(UNICODE_UPPERCASE_LETTER, uppercase_letter);
        TYPE2ID(UNICODE_COMBINING_MARK, combining_mark);
        TYPE2ID(UNICODE_ENCLOSING_MARK, enclosing_mark);
        TYPE2ID(UNICODE_NON_SPACING_MARK, non_spacing_mark);
        TYPE2ID(UNICODE_DECIMAL_NUMBER, decimal_number);
        TYPE2ID(UNICODE_LETTER_NUMBER, letter_number);
        TYPE2ID(UNICODE_OTHER_NUMBER, other_number);
        TYPE2ID(UNICODE_CONNECT_PUNCTUATION, connect_punctuation);
        TYPE2ID(UNICODE_DASH_PUNCTUATION, dash_punctuation);
        TYPE2ID(UNICODE_CLOSE_PUNCTUATION, close_punctuation);
        TYPE2ID(UNICODE_FINAL_PUNCTUATION, final_punctuation);
        TYPE2ID(UNICODE_INITIAL_PUNCTUATION, initial_punctuation);
        TYPE2ID(UNICODE_OTHER_PUNCTUATION, other_punctuation);
        TYPE2ID(UNICODE_OPEN_PUNCTUATION, open_punctuation);
        TYPE2ID(UNICODE_CURRENCY_SYMBOL, currency_symbol);
        TYPE2ID(UNICODE_MODIFIER_SYMBOL, modifier_symbol);
        TYPE2ID(UNICODE_MATH_SYMBOL, math_symbol);
        TYPE2ID(UNICODE_OTHER_SYMBOL, other_symbol);
        TYPE2ID(UNICODE_LINE_SEPARATOR, line_separator);
        TYPE2ID(UNICODE_PARAGRAPH_SEPARATOR, paragraph_separator);
        TYPE2ID(UNICODE_SPACE_SEPARATOR, space_separator);

        switch (type) {
        case UNICODE_CONTROL:
                return ID2SYM(id_control);
        case UNICODE_FORMAT:
                return ID2SYM(id_format);
        case UNICODE_UNASSIGNED:
                return ID2SYM(id_unassigned);
        case UNICODE_PRIVATE_USE:
                return ID2SYM(id_private_use);
        case UNICODE_SURROGATE:
                return ID2SYM(id_surrogate);
        case UNICODE_LOWERCASE_LETTER:
                return ID2SYM(id_lowercase_letter);
        case UNICODE_MODIFIER_LETTER:
                return ID2SYM(id_modifier_letter);
        case UNICODE_OTHER_LETTER:
                return ID2SYM(id_other_letter);
        case UNICODE_TITLECASE_LETTER:
                return ID2SYM(id_titlecase_letter);
        case UNICODE_UPPERCASE_LETTER:
                return ID2SYM(id_uppercase_letter);
        case UNICODE_COMBINING_MARK:
                return ID2SYM(id_combining_mark);
        case UNICODE_ENCLOSING_MARK:
                return ID2SYM(id_enclosing_mark);
        case UNICODE_NON_SPACING_MARK:
                return ID2SYM(id_non_spacing_mark);
        case UNICODE_DECIMAL_NUMBER:
                return ID2SYM(id_decimal_number);
        case UNICODE_LETTER_NUMBER:
                return ID2SYM(id_letter_number);
        case UNICODE_OTHER_NUMBER:
                return ID2SYM(id_other_number);
        case UNICODE_CONNECT_PUNCTUATION:
                return ID2SYM(id_connect_punctuation);
        case UNICODE_DASH_PUNCTUATION:
                return ID2SYM(id_dash_punctuation);
        case UNICODE_CLOSE_PUNCTUATION:
                return ID2SYM(id_close_punctuation);
        case UNICODE_FINAL_PUNCTUATION:
                return ID2SYM(id_final_punctuation);
        case UNICODE_INITIAL_PUNCTUATION:
                return ID2SYM(id_initial_punctuation);
        case UNICODE_OTHER_PUNCTUATION:
                return ID2SYM(id_other_punctuation);
        case UNICODE_OPEN_PUNCTUATION:
                return ID2SYM(id_open_punctuation);
        case UNICODE_CURRENCY_SYMBOL:
                return ID2SYM(id_currency_symbol);
        case UNICODE_MODIFIER_SYMBOL:
                return ID2SYM(id_modifier_symbol);
        case UNICODE_MATH_SYMBOL:
                return ID2SYM(id_math_symbol);
        case UNICODE_OTHER_SYMBOL:
                return ID2SYM(id_other_symbol);
        case UNICODE_LINE_SEPARATOR:
                return ID2SYM(id_line_separator);
        case UNICODE_PARAGRAPH_SEPARATOR:
                return ID2SYM(id_paragraph_separator);
        case UNICODE_SPACE_SEPARATOR:
                return ID2SYM(id_space_separator);
        default:
                rb_raise(rb_eNotImpError, "unknown type: %d", type);
        }
}

VALUE
rb_u_string_type(VALUE self)
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
                        rb_raise(rb_eArgError,
                                 "string consists of more than one type: :%s+, :%s",
                                 rb_id2name(SYM2ID(type_to_symbol(current))),
                                 rb_id2name(SYM2ID(type_to_symbol(type))));

                p = u_next(p);
        }

        return type_to_symbol(current);
}
