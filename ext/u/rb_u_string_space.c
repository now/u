#include "rb_includes.h"

/* Tests if this {U::String} only contains characters in the Separator Unicode
 * category, that is, characters that belong to any of the categories
 *
 * * Separator, space (Zs)
 * * Separator, line (Zl)
 * * Separator, paragraph (Zp)
 *
 * such as ‘ ’, or a control character acting as such, namely
 *
 * * U+0009 (CHARACTER TABULATION (HT))
 * * U+000A (LINE FEED (LF))
 * * U+000C (FORM FEED (FF))
 * * U+000D (CARRIAGE RETURN (CR))
 *
 * @return [Boolean] `True` if this {U::String} only contains characters in the
 *   Separator Unicode category and/or control characters acting as
 *   separators. */
VALUE
rb_u_string_space(VALUE self)
{
        return _rb_u_character_test(self, unichar_isspace);
}
