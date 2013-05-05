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
        return _rb_u_string_convert_locale(argc, argv, self, u_collation_key, "LC_COLLATE");
}
