#include "rb_includes.h"

/* Checks if this {U::String} has been downcased.
 *
 * @overload lower?
 *
 *   Checks if this {U::String} has been downcased according to the rules of the
 *   locale specified by the environment variable `LC_CTYPE`.
 *
 *   The actual check is if _a_ = _a_{#downcase}, where _a_ =
 *   `self`{#normalize}`(:nfd)`.
 *
 *   @return [Boolean] `True` if `self` has been downcased
 *
 * @overload lower?(locale)
 *
 *   Checks if this {U::String} has been downcased according to the rules of
 *   _locale_.
 *
 *   The actual check is if _a_ = _a_{#downcase}`(locale)`, where _a_ =
 *   `self`{#normalize}`(:nfd)`.
 *
 *   @param [#to_str] locale Locale whose casing rules to use
 *   @return [Boolean] `True` if `self` has been downcased */
VALUE
rb_u_string_lower(int argc, VALUE *argv, VALUE self)
{
        return _rb_u_string_test_in_locale(argc, argv, self, u_downcase_in_locale_n);
}
