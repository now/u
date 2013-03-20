#include "rb_includes.h"
#include "rb_u_string_to_inum.h"

/* @overload to_i(base = 16)
 *
 * Converts `self` to an Integer, treating it as a string of digits in _base_.
 *
 * The conversion is done by
 *
 * * Skip any leading {#space?}s
 * * Check for an optional sign, ‘+’ or ‘-’
 * * If base is 2, skip an optional “0b” or “0B” prefix
 * * If base is 8, skip an optional “0o” or “0o” prefix
 * * If base is 10, skip an optional “0d” or “0D” prefix
 * * If base is 16, skip an optional “0x” or “0X” prefix
 * * Skip any ‘0’s
 * * Read an as long sequence of digits in _base_ separated by optional U+005F
 *   LOW LINE characters, using letters in the following ranges of characters
 *   for digits or the characters digit value, if any
 *
 *   * U+0041 LATIN CAPITAL LETTER A through U+005A LATIN CAPITAL LETTER Z
 *   * U+0061 LATIN SMALL LETTER A through U+007A LATIN SMALL LETTER Z
 *   * U+FF21 FULLWIDTH LATIN CAPITAL LETTER A through U+FF3A FULLWIDTH LATIN CAPITAL LETTER Z
 *   * U+FF41 FULLWIDTH LATIN SMALL LETTER A through U+FF5A FULLWIDTH LATIN SMALL LETTER Z
 *
 * Note that only one separator is allowed in a row.
 *
 * @param [Integer] base Number base for conversion
 * @raise [ArgumentError] Unless 2 ≤ _base_ ≤ 36
 * @return [Integer] Value of `self` expressed as an Integer in _base_ */
VALUE
rb_u_string_to_i(int argc, VALUE *argv, VALUE self)
{
        int base = 10;

        VALUE rbbase;
        if (rb_scan_args(argc, argv, "01", &rbbase) == 1)
                base = NUM2INT(rbbase);

        if (base < 0)
                rb_u_raise(rb_eArgError, "illegal radix %d", base);

        return rb_u_string_to_inum(self, base, false);
}
