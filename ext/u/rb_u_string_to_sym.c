#include "rb_includes.h"

/* @overload to_sym
 *
 * Creates a Symbol of this {U::String}.
 *
 * @raise [EncodingError] If `self` contains an invalid UTF-8 sequence
 * @raise [RuntimeError] If there’s no more room for a new Symbol in Ruby’s
 *   Symbol table
 * @return [Symbol] Symbol of this {U::String} */
VALUE
rb_u_string_to_sym(VALUE self)
{
        /* NOTE: Lazy, but MRI makes it hard to implement this method. */
        return rb_str_intern(StringValue(self));
}
