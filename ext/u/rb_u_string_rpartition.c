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
        const struct rb_u_string *string = RVAL2USTRING(self);
        const struct rb_u_string *separator = RVAL2USTRING_ANY(rbseparator);

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
        const struct rb_u_string *string = RVAL2USTRING(self);
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
 *   @param [Regexp, #to_str] separator
 *   @return [Array<U::String>] The receiver split into _s₁_ = {#slice}(0, _i_),
 *     _s₂_ = {#slice}(_i_, _n_), _s₃_ = {#slice}(_i_ + _n_, -1), where _i_ = _j_ if _j_ ≠
 *     nil, _i_ = 0 otherwise, _j_ = {#rindex}(SEPARATOR), _n_ =
 *     SEPARATOR{#length}, where _s₁_ and _s₃_ inherit any taint and untrust
 *     from the receiver and _s₂_ inherits any taint and untrust from SEPARATOR
 *     and also from the receiver if SEPARATOR is a Regexp
 *   @see #partition */
VALUE
rb_u_string_rpartition(VALUE self, VALUE separator)
{
        if (TYPE(separator) == T_REGEXP)
                return rb_u_string_rpartition_regex(self, separator);

        return rb_u_string_rpartition_string(self, separator);
}
