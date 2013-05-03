#include <errno.h>
#include "rb_includes.h"

/* @overload casecmp(other, locale = ENV['LC_COLLATE'])
 *
 *   Returns the comparison of {#foldcase} to _other_{#foldcase} using the
 *   linguistically correct rules of LOCALE.  This is, however, only an
 *   approximation of a case-insensitive comparison.  The LOCALE must be given
 *   as a language, region, and encoding, for example, “en_US.UTF-8”.
 *
 *   This operation is known as “collation” and you can find more information
 *   about the collation algorithm employed in the
 *   Unicode Technical Standard #10, see http://unicode.org/reports/tr10/.
 *
 *   @param [U::String, #to_str] other
 *   @param [#to_str] locale
 *   @return [Fixnum] */
VALUE
rb_u_string_casecmp(int argc, VALUE *argv, VALUE self)
{
        const char *locale = NULL;

        VALUE rbother, rblocale;
        if (rb_scan_args(argc, argv, "11", &rbother, &rblocale) == 2)
                locale = StringValuePtr(rblocale);

        const struct rb_u_string *string = RVAL2USTRING(self);
        const struct rb_u_string *other = RVAL2USTRING_ANY(rbother);

        rb_u_validate(USTRING_STR(string), USTRING_LENGTH(string));
        rb_u_validate(USTRING_STR(other), USTRING_LENGTH(other));

        size_t folded_n = u_foldcase(NULL, 0,
                                     USTRING_STR(string), USTRING_LENGTH(string));
        char *folded = ALLOC_N(char, folded_n + 1);
        u_foldcase(folded, folded_n + 1,
                   USTRING_STR(string), USTRING_LENGTH(string));

        size_t folded_other_n = u_foldcase(NULL, 0,
                                           USTRING_STR(other), USTRING_LENGTH(other));
        char *folded_other = ALLOC_N(char, folded_other_n + 1);
        u_foldcase(folded_other, folded_other_n + 1,
                   USTRING_STR(other), USTRING_LENGTH(other));

        errno = 0;
        int r = u_collate_in_locale_n(folded, folded_n,
                                      folded_other, folded_other_n,
                locale);

        free(folded_other);
        free(folded);

        if (errno != 0)
                rb_u_raise_errno(rb_eSystemCallError, errno, "can’t collate strings");

        return INT2FIX(r);
}
