#include "rb_includes.h"

/* @overload upcase(locale = ENV['LC_CTYPE'])
 *   @param [#to_str] locale
 *   @return [U::String] The upcasing of the receiver according to the rules of
 *     of the language of LOCALE, which may be empty to specifically use the
 *     default, language-independent, rules, inheriting any taint and untrust */
VALUE
rb_u_string_upcase(int argc, VALUE *argv, VALUE self)
{
        return _rb_u_string_convert_locale(argc, argv, self, u_upcase, NULL);
}
