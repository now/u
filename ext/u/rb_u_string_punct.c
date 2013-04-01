#include "rb_includes.h"

/* @overload punct?
 *   @return [Boolean] True if the receiver contains only characters in the
 *     general categories Punctuation and Symbol */
VALUE
rb_u_string_punct(VALUE self)
{
        return _rb_u_character_test(self, u_char_ispunct);
}
