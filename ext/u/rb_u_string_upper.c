#include "rb_includes.h"

/* @overload upper?(locale = ENV[LC_CTYPE])
 *   @param [#to_str] locale
 *   @return [Boolean] True if the receiver has been upcased according to the
 *     rules of the language of LOCALE, which may be empty to specifically use
 *     the default, language-independent, rules, that is, if _a_ =
 *     _a_{#upcase}(LOCALE), where _a_ = {#normalize}(`:nfd`) */
VALUE
rb_u_string_upper(int argc, VALUE *argv, VALUE self)
{
        return _rb_u_string_test_locale(argc, argv, self, u_upcase);
}
