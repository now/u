#include "rb_includes.h"

/* @overload downcase(locale = ENV['LC_CTYPE'])
 *   @param [#to_str] locale
 *   @return [U::String] The downcasing of the receiver according to the rules
 *     of LOCALE, inhereting any taint and untrust */
VALUE
rb_u_string_downcase(int argc, VALUE *argv, VALUE self)
{
        const char *locale = NULL;

        VALUE rblocale;
        if (rb_scan_args(argc, argv, "01", &rblocale) == 1)
                locale = StringValuePtr(rblocale);

        const UString *string = RVAL2USTRING(self);

        size_t length;
        char *downcased = u_downcase_in_locale_n(USTRING_STR(string),
                                                 USTRING_LENGTH(string),
                                                 locale,
                                                 &length);

        return rb_u_string_new_c_own(self, downcased, length);
}
