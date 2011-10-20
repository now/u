#include "rb_includes.h"

/* Tests if this {U::String} only contains zero-width characters.  A zero-width
 * character is defined as a character in the Mark, nonspacing (Mn) or Mark,
 * enclosing (Me) or Other, format (Of) categories, excluding the character
 * U+00AD (SOFT HYPHEN), or is a Hangul character between U+1160 and U+1200 or
 * U+200B (ZERO WIDTH SPACE).
 *
 * @return [Boolean] `True` if this {U::String} only contains zero-width
 *   characters. */
VALUE
rb_u_string_zero_width(VALUE self)
{
        return _rb_u_character_test(self, unichar_iszerowidth);
}
