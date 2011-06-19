#include "rb_includes.h"

VALUE
rb_u_string_downcase(int argc, VALUE *argv, VALUE self)
{
        const char *locale = NULL;

        VALUE rblocale;
        if (rb_scan_args(argc, argv, "01", &rblocale) == 1)
                locale = StringValuePtr(rblocale);

        const UString *string = RVAL2USTRING(self);

        size_t length;
        char *downcased = locale != NULL ?
                u_downcase_in_locale_n(USTRING_STR(string),
                                       USTRING_LENGTH(string),
                                       locale,
                                       &length) :
                u_downcase_n(USTRING_STR(string),
                             USTRING_LENGTH(string),
                             &length);

        return rb_u_string_new_own(downcased, length);
}
