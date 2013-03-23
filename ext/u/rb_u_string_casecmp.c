#include "rb_includes.h"

/* @overload casecmp(other)
 *
 *   Returns the comparison of {#foldcase} to _other_{#foldcase} using the
 *   linguistically correct rules of the current locale.  This is, however,
 *   only an approximation of a case-insensitive comparison.
 *
 *   This operation is known as “collation” and you can find more information
 *   about the collation algorithm employed in the
 *   Unicode Technical Standard #10, see http://unicode.org/reports/tr10/.
 *
 *   @param [U::String, #to_str] other
 *   @return [Fixnum] */
VALUE
rb_u_string_casecmp(VALUE self, VALUE rbother)
{
        const UString *string = RVAL2USTRING(self);
        const UString *other = RVAL2USTRING_ANY(rbother);

        size_t folded_length;
        char *folded = u_foldcase_n(USTRING_STR(string),
                                    USTRING_LENGTH(string),
                                    &folded_length);

        size_t folded_other_length;
        char *folded_other = u_foldcase_n(USTRING_STR(other),
                                          USTRING_LENGTH(other),
                                          &folded_other_length);

        int result = u_collate_n(folded, folded_length,
                                 folded_other, folded_other_length);

        free(folded_other);
        free(folded);

        return INT2FIX(result);
}
