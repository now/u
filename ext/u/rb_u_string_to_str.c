#include "rb_includes.h"

#ifdef HAVE_RUBY_ENCODING_H
#  include <ruby/encoding.h>
#endif

/* @overload to_s
 * @overload to_str
 *
 * Converts this {U::String} to a String.
 *
 * Any taint or untrust is inherited.
 *
 * @return [String] `self` converted to a String */
VALUE
rb_u_string_to_str(VALUE self)
{
        const UString *string = RVAL2USTRING(self);

        VALUE result;

        if (!NIL_P(string->rb))
                result = string->rb;
        else
                result =
                /* TODO: Check all rb_str_new calls. */
#ifdef HAVE_RUBY_ENCODING_H
                rb_enc_str_new(USTRING_STR(string), USTRING_LENGTH(string), rb_utf8_encoding());
#else
                rb_str_new(USTRING_STR(string), USTRING_LENGTH(string));
#endif

        OBJ_INFECT(result, self);

        return result;
}
