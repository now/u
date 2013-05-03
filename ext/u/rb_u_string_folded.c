#include "rb_includes.h"

/* @overload folded?
 *   @return [Boolean] True if the receiver has been case-folded, that is, if
 *     _a_ = _a_{#foldcase}, where _a_ = {#normalize}(`:nfd`) */
VALUE
rb_u_string_folded(VALUE self)
{
        return _rb_u_string_test(self, u_foldcase);
}
