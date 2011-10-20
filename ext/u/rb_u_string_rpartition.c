#include "rb_includes.h"
#include "rb_u_re.h"

static VALUE
rb_u_string_rpartition_failure(VALUE self)
{
        return rb_ary_new3(3,
                           rb_u_string_new_empty(self),
                           rb_u_string_new_empty(self),
                           self);
}

static VALUE
rb_u_string_rpartition_success(VALUE self, VALUE rbseparator, long offset)
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
rb_u_string_rpartition_regex(VALUE self, VALUE regex)
{
        VALUE str = rb_str_to_str(self);

        long offset = rb_reg_search(regex, str, RSTRING_LEN(str), 1);
        if (offset < 0)
                return rb_u_string_rpartition_failure(self);

        VALUE separator = rb_u_pattern_match_reference(INT2FIX(0));

        return rb_u_string_rpartition_success(self, separator, offset);
}

static VALUE
rb_u_string_rpartition_string(VALUE self, VALUE rbseparator)
{
        const UString *string = RVAL2USTRING(self);
        const char *begin = USTRING_STR(string);

        VALUE validated = rb_u_string_validate_type(rbseparator);

        long offset = rb_u_string_rindex(self,
                                         validated,
                                         u_length_n(begin,
                                                    USTRING_LENGTH(string)));
        if (offset < 0)
                return rb_u_string_rpartition_failure(self);

        long byte_offset = u_offset_to_pointer(begin, offset) - begin;

        return rb_u_string_rpartition_success(self, validated, byte_offset);
}

/* @overload rpartition(separator)
 *
 * Splits this {U::String} into {#slice}(0, _i_), {#slice}(_i_, _n_),
 * {#slice}(_i_ + _n_, -1), where _i_ = _j_ if _j_ ≠ `nil`, _i_ = 0
 * otherwise, _j_ = {#rindex}(_separator_), _n_ =
 * _separator_{#length}.
 *
 * @param [Regexp, #to_str] separator Separator to use for splitting
 * @return [Array<U::String>] `self` split around the last match of _separator_
 * @see #partition */
VALUE
rb_u_string_rpartition(VALUE self, VALUE separator)
{
        if (TYPE(separator) == T_REGEXP)
                return rb_u_string_rpartition_regex(self, separator);

        return rb_u_string_rpartition_string(self, separator);
}
