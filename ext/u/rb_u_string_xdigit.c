#include "rb_includes.h"

/* Tests if this {U::String} only contains characters in the Number, decimal
 * digit (Nd) category or is a lower- or uppercase letter between ‘a’ and ‘f’.
 * Specifically, any character that
 *
 * * Belongs to the Number, decimal digit (Nd) category
 * * Falls in the range U+0041 (LATIN CAPITAL LETTER A) through U+0046 (LATIN CAPITAL LETTER F)
 * * Falls in the range U+0061 (LATIN SMALL LETTER A) through U+0066 (LATIN SMALL LETTER F)
 * * Falls in the range U+FF21 (FULLWIDTH LATIN CAPITAL LETTER A) through U+FF26 (FULLWIDTH LATIN CAPITAL LETTER F)
 * * Falls in the range U+FF41 (FULLWIDTH LATIN SMALL LETTER A) through U+FF46 (FULLWIDTH LATIN SMALL LETTER F)
 *
 * will do.
 *
 * @return [Boolean] `True` if this {U::String} only contains characters in the
 *   Number, decimal digit (Nd) category or is a lower- or uppercase letter
 *   between ‘a’ and ‘f’. */
VALUE
rb_u_string_xdigit(VALUE self)
{
        return _rb_u_character_test(self, unichar_isxdigit);
}
