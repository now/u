#include "rb_includes.h"
#include "rb_u_re.h"

/* @overload =~(other)
 *   @param [Regexp, #=~] other
 *   @raise [TypeError] If OTHER is a {U::String} or String
 *   @return [Numeric, nil] The result of OTHER`#=~`(self), that is, the index
 *     of the first character of the match of OTHER in the receiver, if one
 *     exists */
VALUE
rb_u_string_match(VALUE self, VALUE other)
{
        if (RTEST(rb_obj_is_kind_of(other, rb_cUString)))
                rb_u_raise(rb_eTypeError, "type mismatch: U::String given");

        switch (TYPE(other)) {
        case T_STRING:
                rb_u_raise(rb_eTypeError, "type mismatch: String given");
                break;
        case T_REGEXP: {
                const struct rb_u_string *string = RVAL2USTRING(self);

                /* TODO: This needs to be made more efficient. */
                long index = rb_reg_search(other, rb_str_to_str(self), 0, 0);
                if (index < 0)
                        return Qnil;

                return LONG2NUM(u_pointer_to_offset(USTRING_STR(string),
                                                    USTRING_STR(string) + index));
        }
        default:
                return rb_funcall(other, rb_intern("=~"), 1, self);
        }
}

/* @overload match(pattern, index = 0)
 *   @param [Regexp, #to_str] pattern
 *   @param [#to_int] index
 *   @return [MatchData, nil] The result of _r_#match(self, index), that is,
 *     the match data of the first match of _r_ in the receiver, inheriting any
 *     taint and untrust from both the receiver and from PATTERN, if one
 *     exists, where _r_ = PATTERN, if PATTERN is a Regexp, _r_ =
 *     Regexp.new(PATTERN) otherwise
 * @overload match(pattern, index = 0){ |matchdata| … }
 *   @param [Regexp, #to_str] pattern
 *   @param [#to_int] index
 *   @yieldparam [MatchData] matchdata
 *   @return [Object, nil] The result of calling the given block with the
 *     result of _r_#match(self, index), that is, the match data of the first
 *     match of _r_ in the receiver, inheriting any taint and untrust from both
 *     the recevier and from PATTERN, if one exists, where _r_ = PATTERN, if
 *     PATTERN is a Regexp, _r_ = Regexp.new(PATTERN) otherwise */
VALUE
rb_u_string_match_m(int argc, VALUE *argv, VALUE self)
{
        VALUE re;
        if (argc < 0)
                need_m_to_n_arguments(argc, 1, 2);
        re = argv[0];
        argv[0] = self;
        VALUE result = rb_funcall2(rb_u_pattern_argument(re, false),
                                   rb_intern("match"), argc, argv);
        if (!NIL_P(result) && rb_block_given_p())
                return rb_yield(result);
        return result;
}
