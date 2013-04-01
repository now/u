#include "rb_includes.h"

/* @overload cased?
 *
 *   @return [Boolean] True if the receiver only contains characters in the
 *     general categories
 *
 *     * Letter, uppercase (Lu)
 *     * Letter, lowercase (Ll)
 *     * Letter, titlecase (Lt)
 *
 *     or has the derived properties Other_Uppercase or Other_Lowercase */
VALUE
rb_u_string_cased(VALUE self)
{
        return _rb_u_character_test(self, u_char_iscased);
}
