#include "rb_includes.h"
#include "rb_u_re.h"

static VALUE
rb_u_string_partition_failure(VALUE self)
{
        return rb_ary_new3(3,
                           self,
                           rb_u_string_new_empty(self),
                           rb_u_string_new_empty(self));
}

static VALUE
rb_u_string_partition_success(VALUE self, VALUE rbseparator, long offset)
{
        const UString *string = RVAL2USTRING(self);
        const UString *separator = RVAL2USTRING_ANY(rbseparator);

        long after = offset + USTRING_LENGTH(separator);

        return rb_ary_new3(3,
                           rb_u_string_new_subsequence(self, 0, offset),
                           TYPE(rbseparator) == T_STRING ?
                                rb_u_string_new_rb(rbseparator) :
                                rbseparator,
                           rb_u_string_new_subsequence(self,
                                                       after,
                                                       USTRING_LENGTH(string) - after));
}

static VALUE
rb_u_string_partition_regex(VALUE self, VALUE regex)
{
        VALUE str = rb_str_to_str(self);

        long offset = rb_reg_search(regex, str, 0, 0);
        if (offset < 0)
                return rb_u_string_partition_failure(self);

        VALUE separator = rb_u_pattern_match_reference(INT2FIX(0));

        if (offset == 0 && RSTRING_LEN(separator) == 0)
                return rb_u_string_partition_failure(self);

        return rb_u_string_partition_success(self, separator, offset);
}

static VALUE
rb_u_string_partition_string(VALUE self, VALUE rbseparator)
{
        VALUE validated = rb_u_string_validate_type(rbseparator);

        long offset = rb_u_string_index(self, validated, 0);
        if (offset < 0)
                return rb_u_string_partition_failure(self);

        const char *begin = USTRING_STR(RVAL2USTRING(self));
        long byte_offset = u_offset_to_pointer(begin, offset) - begin;

        return rb_u_string_partition_success(self, validated, byte_offset);
}

VALUE
rb_u_string_partition(VALUE self, VALUE separator)
{
        if (TYPE(separator) == T_REGEXP)
                return rb_u_string_partition_regex(self, separator);

        return rb_u_string_partition_string(self, separator);
}
