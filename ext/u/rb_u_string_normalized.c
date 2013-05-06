#include "rb_includes.h"

/* @overload normalize?(mode = :default)
 *
 *   Returns true if it can be determined that the receiver is normalized
 *   according to MODE.
 *
 *   See {#normalize} for a discussion on normalization and a list of the
 *   possible normalization modes.
 *
 *   @param [#to_sym] mode
 *   @return [Boolean]
 *   @see http://unicode.org/reports/tr15/
 *     Unicode Standard Annex #15: Unicode Normalization Forms */
VALUE
rb_u_string_normalized(int argc, VALUE *argv, VALUE self)
{
        const struct rb_u_string *string = RVAL2USTRING(self);

        VALUE rbform;
        enum u_normalization_form form = U_NORMALIZATION_FORM_D;
        if (rb_scan_args(argc, argv, "01", &rbform) == 1)
                form = _rb_u_symbol_to_normalization_form(rbform);

        return u_normalized(USTRING_STR(string),
                            USTRING_LENGTH(string),
                            form) == U_NORMALIZED_YES ? Qtrue : Qfalse;
}
