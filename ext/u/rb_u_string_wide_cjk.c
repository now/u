#include "rb_includes.h"

VALUE
rb_u_string_wide_cjk(VALUE self)
{
        return _rb_u_character_test(self, unichar_iswide_cjk);
}
