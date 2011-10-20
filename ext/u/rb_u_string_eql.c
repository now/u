#include "rb_includes.h"

/* @overload ==(other)
 *
 *   Compares `self` to _other_ without considering the linguistically correct
 *   rules of the current locale.
 *
 *   This comparison only takes into account the actual byte representation of
 *   the two strings.  You may want to use {#<=>} for a more appropriate
 *   comparison method.
 *
 *   @param [U::String] other The string to compare this {U::String} to
 *   @return [Boolean] `True` if `self` is equal to _other_ */
VALUE
rb_u_string_eql(VALUE self, VALUE rbother)
{
        if (self == rbother)
                return Qtrue;

        if (!rb_obj_is_kind_of(rbother, rb_cUString))
                return Qfalse;

        const UString *string = RVAL2USTRING(self);
        const UString *other = RVAL2USTRING(rbother);

        const char *p = USTRING_STR(string);
        const char *q = USTRING_STR(other);

        if (p == q)
                return Qtrue;

        long p_length = USTRING_LENGTH(string);
        long q_length = USTRING_LENGTH(other);

        return p_length == q_length && memcmp(p, q, q_length) == 0 ? Qtrue : Qfalse;
}
