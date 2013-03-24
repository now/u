#include "rb_includes.h"

/* @return [U::String] The receiver with its maximum {#space?} prefix removed,
 *   inheriting any taint and untrust
 * @see #rstrip
 * @see #strip */
VALUE
rb_u_string_lstrip(VALUE self)
{
        const UString *string = RVAL2USTRING(self);

        const char *begin = USTRING_STR(string);
        if (begin == NULL)
                return self;

        const char *end = USTRING_END(string);
        const char *p = begin;
        while (p < end && unichar_isspace(_rb_u_aref_char_validated(p, end)))
                p = u_next(p);
        if (p == begin)
                return self;

        return rb_u_string_new_c(self, p, end - p);
}
