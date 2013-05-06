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

        VALUE rbmode;
        enum u_normalize_mode mode = U_NORMALIZE_DEFAULT;
        if (rb_scan_args(argc, argv, "01", &rbmode) == 1)
                mode = _rb_u_symbol_to_normalize_mode(rbmode);

        return u_normalized(USTRING_STR(string),
                            USTRING_LENGTH(string),
                            mode) == U_NORMALIZED_YES ? Qtrue : Qfalse;
}
