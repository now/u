#include "rb_includes.h"

/* @overload upcase(locale = ENV['LC_CTYPE'])
 *   @param [#to_str] locale
 *   @return [U::String] The upcasing of the receiver according to the rules of
 *     LOCALE, inheriting any taint and untrust */
VALUE
rb_u_string_upcase(int argc, VALUE *argv, VALUE self)
{
        return _rb_u_string_case_in_locale(argc, argv, self,
                                           u_upcase_in_locale_n);
}
