#include "rb_includes.h"

VALUE
rb_u_string_upcase(int argc, VALUE *argv, VALUE self)
{
        const char *locale = NULL;

        VALUE rblocale;
        if (rb_scan_args(argc, argv, "01", &rblocale) == 1)
                locale = StringValuePtr(rblocale);

        const UString *string = RVAL2USTRING(self);

        size_t length;
        char *upcased = locale != NULL ?
                u_upcase_in_locale_n(USTRING_STR(string),
                                     USTRING_LENGTH(string),
                                     locale,
                                     &length) :
                u_upcase_n(USTRING_STR(string),
                           USTRING_LENGTH(string),
                           &length);

        return rb_u_string_new_own(upcased, length);
}
