#include "rb_includes.h"

VALUE
rb_u_casecmp(VALUE str1, VALUE str2)
{
        StringValue(str1);
        StringValue(str2);

        char *folded1 = utf_foldcase(RSTRING(str1)->ptr);
        char *folded2 = utf_foldcase(RSTRING(str2)->ptr);

        int result = u_collate(folded1, folded2);

        free(folded2);
        free(folded1);

        return INT2FIX(result);
}
