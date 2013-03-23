#include "rb_includes.h"
#include "rb_u_re.h"

/* @overload =~(other)
 *   @param [Regexp, #=~] other
 *   @raise [TypeError] If OTHER is a {U::String} or String
 *   @return [Numeric, nil] The result of OTHER`#=~(self)`, that is, the index
 *     of the first character of the match of OTHER in the receiver, if one
 *     exists */
VALUE
rb_u_string_match(VALUE self, VALUE other)
{
        if (rb_obj_is_kind_of(other, rb_cUString))
                rb_u_raise(rb_eTypeError, "type mismatch: U::String given");

        switch (TYPE(other)) {
        case T_STRING:
                rb_u_raise(rb_eTypeError, "type mismatch: String given");
                break;
        case T_REGEXP: {
                const UString *string = RVAL2USTRING(self);

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
