#include "rb_includes.h"

/* @overload upcase(locale = ENV['LC_CTYPE'])
 *
 * Upcases this {U::String} according to the rules of _locale_.
 *
 * @param [#to_str] locale Locale whose casing rules to use
 * @return [U::String] Upcased version of `self` according to the rules of
 *   _locale_ */
VALUE
rb_u_string_upcase(int argc, VALUE *argv, VALUE self)
{
        const char *locale = NULL;

        VALUE rblocale;
        if (rb_scan_args(argc, argv, "01", &rblocale) == 1)
                locale = StringValuePtr(rblocale);

        const UString *string = RVAL2USTRING(self);

        size_t length;
        char *upcased = u_upcase_in_locale_n(USTRING_STR(string),
                                             USTRING_LENGTH(string),
                                             locale,
                                             &length);

        return rb_u_string_new_own(upcased, length);
}
