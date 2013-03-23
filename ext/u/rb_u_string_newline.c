#include "rb_includes.h"

/* @overload newline?
 *
 *   Returns true if the receiver contains only “newline” characters.  A
 *   character is a “newline” character if it is any of the following
 *   characters:
 *
 *   * U+000A (LINE FEED (LF))
 *   * U+000C (FORM FEED (FF))
 *   * U+000D (CARRIAGE RETURN (CR))
 *   * U+0085 (NEXT LINE)
 *   * U+2028 (LINE SEPARATOR)
 *   * U+2029 (PARAGRAPH SEPARATOR)
 *
 *   @return [Boolean] */
VALUE
rb_u_string_newline(VALUE self)
{
        return _rb_u_character_test(self, unichar_isnewline);
}
