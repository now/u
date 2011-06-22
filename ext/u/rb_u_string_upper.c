#include "rb_includes.h"

VALUE
rb_u_string_upper(int argc, VALUE *argv, VALUE self)
{
        return _rb_u_string_test_in_locale(argc, argv, self, u_upcase_in_locale_n);
}
