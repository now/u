#include "rb_includes.h"

/* @overload <=>(other)
 *
 *   Compares `self` to _other_ using the linguistically correct rules of the
 *   current locale.
 *
 *   This operation is known as “collation” and you can find more information
 *   about the collation algorithm employed in the
 *   Unicode Technical Standard #10, see http://unicode.org/reports/tr10/.
 *
 *   @param [U::String, #to_str] other String to compare this {U::String} to
 *   @return [Fixnum] A number _n_, where _n_ < 0, _n_ = 0, or _n_ > 0, if
 *     `self` comes before, is the same as, or comes after _other_,
 *     respectively */
VALUE
rb_u_string_collate(VALUE self, VALUE rbother)
{
        const UString *string = RVAL2USTRING(self);
        const UString *other = RVAL2USTRING_ANY(rbother);

        return INT2FIX(u_collate_n(USTRING_STR(string), USTRING_LENGTH(string),
                                   USTRING_STR(other), USTRING_LENGTH(other)));
}
