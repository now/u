#include "rb_includes.h"

/* @overload xdigit?
 *
 *   Returns true if the receiver contains only characters in the general
 *   category Number, decimal digit (Nd) or is a lower- or uppercase letter
 *   between ‘a’ and ‘f’.  Specifically, any character that
 *
 *   * Belongs to the general category Number, decimal digit (Nd)
 *   * Falls in the range U+0041 (LATIN CAPITAL LETTER A) through U+0046 (LATIN CAPITAL LETTER F)
 *   * Falls in the range U+0061 (LATIN SMALL LETTER A) through U+0066 (LATIN SMALL LETTER F)
 *   * Falls in the range U+FF21 (FULLWIDTH LATIN CAPITAL LETTER A) through U+FF26 (FULLWIDTH LATIN CAPITAL LETTER F)
 *   * Falls in the range U+FF41 (FULLWIDTH LATIN SMALL LETTER A) through U+FF46 (FULLWIDTH LATIN SMALL LETTER F)
 *
 *   will do.
 *
 *   @return [Boolean] */
VALUE
rb_u_string_xdigit(VALUE self)
{
        return _rb_u_character_test(self, unichar_isxdigit);
}
