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
 *   @raise [Errno::EILSEQ] If a character in the receiver can’t be converted
 *     into the encoding of the locale
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
        else {
                const char * const env[] = { "LC_ALL", "LC_COLLATE", "LANG", NULL };
                for (const char * const *p = env; *p != NULL; p++)
                        if ((locale = getenv(*p)) != NULL)
                                break;
        }

        const struct rb_u_string *string = RVAL2USTRING(self);
        const struct rb_u_string *other = RVAL2USTRING_ANY(rbother);

        errno = 0;
        int r = u_collate(USTRING_STR(string), USTRING_LENGTH(string),
                          USTRING_STR(other), USTRING_LENGTH(other),
                          locale);
        if (errno != 0)
                rb_u_raise_errno(errno, "can’t collate strings");
        return INT2FIX(r);
}
