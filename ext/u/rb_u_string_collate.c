#include "rb_includes.h"
#include <errno.h>

/* @overload <=>(other)
 *
 *   Returns the comparison of the receiver and OTHER using the linguistically
 *   correct rules of the current locale.
 *
 *   This operation is known as “collation” and you can find more information
 *   about the collation algorithm employed in the
 *   Unicode Technical Standard #10, see http://unicode.org/reports/tr10/.
 *
 *   @param [U::String, #to_str] other
 *   @return [Fixnum]
 *   @see #==
 *   @see #eql? */
VALUE
rb_u_string_collate(VALUE self, VALUE rbother)
{
        const struct rb_u_string *string = RVAL2USTRING(self);
        const struct rb_u_string *other = RVAL2USTRING_ANY(rbother);

        errno = 0;
        int r = u_collate_n(USTRING_STR(string), USTRING_LENGTH(string),
                            USTRING_STR(other), USTRING_LENGTH(other));
        if (errno != 0)
                rb_u_raise_errno(rb_eSystemCallError, errno, "can’t collate strings");
        return INT2FIX(r);
}
