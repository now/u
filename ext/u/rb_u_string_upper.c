#include "rb_includes.h"

/* Checks if this {U::String} has been uppercased.
 *
 * @overload upper?
 *
 *   Checks if this {U::String} has been uppercased according to the rules of
 *   the locale specified by the environment variable `LC_CTYPE`.
 *
 *   The actual check is if _a_ = _a_{#upcase}, where _a_ =
 *   `self`{#normalize}`(:nfd)`.
 *
 *   @return [Boolean] `True` if `self` has been uppercased
 *
 * @overload upper?(locale)
 *
 *   Checks if this {U::String} has been uppercased according to the rules of
 *   _locale_.
 *
 *   The actual check is if _a_ = _a_{#upcase}`(locale)`, where _a_ =
 *   `self`{#normalize}`(:nfd)`.
 *
 *   @param [#to_str] locale Locale whose casing rules to use
 *   @return [Boolean] `True` if `self` has been uppercased */
VALUE
rb_u_string_upper(int argc, VALUE *argv, VALUE self)
{
        return _rb_u_string_test_in_locale(argc, argv, self, u_upcase_in_locale_n);
}
