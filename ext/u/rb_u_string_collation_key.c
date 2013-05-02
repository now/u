#include "rb_includes.h"

/* @overload collation_key(locale = ENV['LC_COLLATE'])
 *
 *   @return [U::String] The locale-dependent collation key of the receiver in
 *     LOCALE, inheriting any taint and untrust
 *   @note Use the collation key when comparing U::Strings to each other
 *     repeatedly, as occurs when, for example, sorting a list of
 *     U::Strings.
 *   @note The LOCALE must be given as a language, region, and encoding, for
 *     example, “en_US.UTF-8”. */
VALUE
rb_u_string_collation_key(int argc, VALUE *argv, VALUE self)
{
        const char *locale = NULL;

        VALUE rblocale;
        if (rb_scan_args(argc, argv, "01", &rblocale) == 1)
                locale = StringValuePtr(rblocale);

        const struct rb_u_string *string = RVAL2USTRING(self);

        rb_u_validate(USTRING_STR(string), USTRING_LENGTH(string));

        size_t length;
        char *cased = u_collation_key_in_locale_n(USTRING_STR(string),
                                                  USTRING_LENGTH(string),
                                                  locale,
                                                  &length);

        return rb_u_string_new_c_own(self, cased, length);
}
