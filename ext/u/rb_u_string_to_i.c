#include "rb_includes.h"
#include "rb_u_string_to_inum.h"

/* @overload to_i(base = 16)
 *
 *   Returns the Integer value that results from treating the receiver as a
 *   string of digits in BASE.
 *
 *   The conversion algorithm is
 *
 *   1. Skip any leading {#space?}s
 *   2. Check for an optional sign, ‘+’ or ‘-’
 *   3. If base is 2, skip an optional “0b” or “0B” prefix
 *   4. If base is 8, skip an optional “0o” or “0o” prefix
 *   5. If base is 10, skip an optional “0d” or “0D” prefix
 *   6. If base is 16, skip an optional “0x” or “0X” prefix
 *   7. Skip any ‘0’s
 *   8. Read an as long sequence of digits in BASE separated by optional U+005F
 *      LOW LINE characters, using letters in the following ranges of characters
 *      for digits or the characters digit value, if any
 *
 *       * U+0041 LATIN CAPITAL LETTER A through U+005A LATIN CAPITAL LETTER Z
 *       * U+0061 LATIN SMALL LETTER A through U+007A LATIN SMALL LETTER Z
 *       * U+FF21 FULLWIDTH LATIN CAPITAL LETTER A through U+FF3A FULLWIDTH LATIN CAPITAL LETTER Z
 *       * U+FF41 FULLWIDTH LATIN SMALL LETTER A through U+FF5A FULLWIDTH LATIN SMALL LETTER Z
 *
 *      Note that only one separator is allowed in a row.
 *
 *   @param [Integer] base
 *   @raise [ArgumentError] Unless 2 ≤ BASE ≤ 36
 *   @return [Integer] */
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
