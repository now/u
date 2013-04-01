#include "rb_includes.h"
#ifdef HAVE_RUBY_ENCODING_H
#  include <ruby/encoding.h>
#endif

/* @return [String] The String representation of the receiver, inheriting any
 *   taint and untrust, encoded as ASCII-8BIT. */
VALUE
rb_u_string_b(VALUE self)
{
        const struct rb_u_string *string = RVAL2USTRING(self);
        VALUE result = rb_str_new(USTRING_STR(string), USTRING_LENGTH(string));
#ifdef HAVE_RUBY_ENCODING_H
        rb_enc_associate(result, rb_ascii8bit_encoding());
#endif
        OBJ_INFECT(result, self);
        return result;
}
