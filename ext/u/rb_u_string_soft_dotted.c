#include "rb_includes.h"

/* @overload soft_dotted?
 *   @return [Boolean] True if this {U::String} only contains soft-dotted
 *     characters
 *   @note Soft-dotted characters have the soft-dotted property and thus lose
 *     their dot if an accent is applied to them, for example, ‘i’ and ‘j’.
 *   @see http://unicode.org/review/pr-11.html Unicode Public Review Issue #11 */
VALUE
rb_u_string_soft_dotted(VALUE self)
{
        return _rb_u_character_test(self, u_char_issoftdotted);
}
