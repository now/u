#include "rb_includes.h"

/* @overload downcase(locale = ENV['LC_CTYPE'])
 *   @param [#to_str] locale
 *   @return [U::String] The downcasing of the receiver according to the rules
 *     of LOCALE, inhereting any taint and untrust */
VALUE
rb_u_string_downcase(int argc, VALUE *argv, VALUE self)
{
        return _rb_u_string_convert_locale(argc, argv, self, u_downcase);
}
