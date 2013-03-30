#include "rb_includes.h"

/* @overload space?
 *
 *   Returns true if the receiver contains only “space” characters.  Space
 *   characters are those in the general category Separator:
 *
 *   * Separator, space (Zs)
 *   * Separator, line (Zl)
 *   * Separator, paragraph (Zp)
 *
 *   such as ‘ ’, or a control character acting as such, namely
 *
 *   * U+0009 CHARACTER TABULATION (HT)
 *   * U+000A LINE FEED (LF)
 *   * U+000C FORM FEED (FF)
 *   * U+000D CARRIAGE RETURN (CR)
 *
 *   @return [Boolean] */
VALUE
rb_u_string_space(VALUE self)
{
        return _rb_u_character_test(self, unichar_isspace);
}
