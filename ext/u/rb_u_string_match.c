#include "rb_includes.h"
#include "rb_u_re.h"

/* @overload =~(other)
 *
 *   Match _other_ against `self` by sending `#=~` to _other_ with `self` as an
 *   argument.
 *
 *   @param [Regexp, #=~] other Object to match against `self`
 *   @raise [TypeError] If _other_ is a {U::String} or `String`
 *   @return [Numeric, nil] The index of the first match of _other_, or `nil`
 *     if no match was found */
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
