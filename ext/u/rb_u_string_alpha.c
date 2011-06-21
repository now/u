#include "rb_includes.h"

VALUE
rb_u_string_alpha(VALUE self)
{
        return _rb_u_character_test(self, unichar_isalpha);
}
