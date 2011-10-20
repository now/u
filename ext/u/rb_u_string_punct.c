#include "rb_includes.h"

/* Tests if this {U::String} only contains characters in the Punctuation or
 * Symbol Unicode categories, that is, characters that belong to any of the
 * categories
 *
 * * Punctuation, connector (Pc)
 * * Punctuation, dash (Pd)
 * * Punctuation, open (Ps)
 * * Punctuation, close (Pe)
 * * Punctuation, initial quote (Pi)
 * * Punctuation, final quote (Pf)
 * * Punctuation, other (Po)
 * * Symbol, math (Sm)
 * * Symbol, currency (Sc)
 * * Symbol, modifier (Sk)
 * * Symbol, other (So)
 *
 * such as ‘.’, ‘$’, and ‘‘’.
 *
 * @return [Boolean] `True` if this {U::String} only contains characters in the
 *   Punctuation or Symbol Unicode categories. */
VALUE
rb_u_string_punct(VALUE self)
{
        return _rb_u_character_test(self, unichar_ispunct);
}
