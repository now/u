#include "rb_includes.h"

VALUE
rb_u_string_upcase(VALUE str)
{
        StringValue(str);

        size_t length;

        char *upcased = utf_upcase_n(RSTRING_PTR(str), RSTRING_LEN(str), &length);
        return rb_u_string_alloc_using_n(upcased, length);
}
