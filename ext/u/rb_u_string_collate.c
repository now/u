#include "rb_includes.h"

VALUE
rb_u_string_collate(VALUE str, VALUE other)
{
        return INT2FIX(u_collate(StringValuePtr(str), StringValuePtr(other)));
}
