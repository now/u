#include "rb_includes.h"
#include <errno.h>

/* @overload <=>(other, locale = ENV['LC_COLLATE'])
 *
 *   Returns the comparison of the receiver and OTHER using the linguistically
 *   correct rules of LOCALE.  The LOCALE must be given as a language, region,
 *   and encoding, for example, “en_US.UTF-8”.
 *
 *   This operation is known as “collation” and you can find more information
 *   about the collation algorithm employed in the
 *   Unicode Technical Standard #10, see http://unicode.org/reports/tr10/.
 *
 *   @param [U::String, #to_str] other
 *   @param [#to_str] locale
 *   @return [Fixnum]
 *   @see #==
 *   @see #eql? */
VALUE
rb_u_string_collate(int argc, VALUE *argv, VALUE self)
{
        const char *locale = NULL;

        VALUE rbother, rblocale;
        if (rb_scan_args(argc, argv, "11", &rbother, &rblocale) == 2)
                locale = StringValuePtr(rblocale);

        const struct rb_u_string *string = RVAL2USTRING(self);
        const struct rb_u_string *other = RVAL2USTRING_ANY(rbother);

        rb_u_validate(USTRING_STR(string), USTRING_LENGTH(string));
        rb_u_validate(USTRING_STR(other), USTRING_LENGTH(other));

        errno = 0;
        int r = u_collate(USTRING_STR(string), USTRING_LENGTH(string),
                          USTRING_STR(other), USTRING_LENGTH(other),
                          locale);
        if (errno != 0)
                rb_u_raise_errno(errno, "can’t collate strings");
        return INT2FIX(r);
}
