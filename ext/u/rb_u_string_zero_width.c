#include "rb_includes.h"

/* @overload zero_width?
 *
 *   Returns true if the receiver contains only “zero-width” characters.  A
 *   zero-width character is defined as a character in the general categories
 *   Mark, nonspacing (Mn), Mark, enclosing (Me) or Other, format (Of),
 *   excluding the character U+00AD (SOFT HYPHEN), or is a Hangul character
 *   between U+1160 and U+1200 or U+200B (ZERO WIDTH SPACE).
 *
 *   @return [Boolean] */
VALUE
rb_u_string_zero_width(VALUE self)
{
        return _rb_u_character_test(self, unichar_iszerowidth);
}
