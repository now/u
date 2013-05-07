#include "rb_includes.h"

/* @overload lower?(locale = ENV[LC_CTYPE])
 *   @param [#to_str] locale
 *   @return [Boolean] True if the receiver has been downcased according to the
 *     rules of the language of LOCALE, which may be empty to specifically use
 *     the default, language-independent, rules, that is, if _a_ =
 *     _a_{#downcase}(LOCALE), where _a_ = {#normalize}(`:nfd`) */
VALUE
rb_u_string_lower(int argc, VALUE *argv, VALUE self)
{
        return _rb_u_string_test_locale(argc, argv, self, u_downcase);
}
