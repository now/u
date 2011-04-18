#include "rb_includes.h"

#ifdef HAVE_RUBY_ENCODING_H
#  include <ruby/encoding.h>
#endif

VALUE
rb_u_string_to_str(VALUE self)
{
        const UString *string = RVAL2USTRING(self);

        if (!NIL_P(string->rb))
                return string->rb;

        /* TODO: Check all rb_str_new calls. */
#ifdef HAVE_RUBY_ENCODING_H
        return rb_enc_str_new(USTRING_STR(string), USTRING_LENGTH(string), rb_utf8_encoding());
#else
        return rb_str_new(USTRING_STR(string), USTRING_LENGTH(string));
#endif
}
