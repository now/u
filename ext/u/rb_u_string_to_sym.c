#include "rb_includes.h"

/* @raise [EncodingError] If the receiver contains an invalid UTF-8 sequence
 * @raise [RuntimeError] If there’s no more room for a new Symbol in Ruby’s
 *   Symbol table
 * @return [Symbol] The Symbol representation of the receiver */
VALUE
rb_u_string_to_sym(VALUE self)
{
        /* NOTE: Lazy, but MRI makes it hard to implement this method. */
        return rb_str_intern(StringValue(self));
}
