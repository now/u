#include "rb_includes.h"

VALUE
rb_u_string_match(VALUE self, VALUE other)
{
        if (rb_obj_is_kind_of(other, rb_cUString))
                rb_raise(rb_eTypeError, "type mismatch: U::String given");

        switch (TYPE(other)) {
        case T_STRING:
                rb_raise(rb_eTypeError, "type mismatch: String given");
                break;
        case T_REGEXP: {
                const UString *string = RVAL2USTRING(self);

                /* TODO: This needs to be made more efficient. */
                VALUE index = rb_reg_match(other, rb_str_to_str(self));
                if (NIL_P(index))
                        return Qnil;

                return LONG2NUM(u_pointer_to_offset(USTRING_STR(string),
                                                    USTRING_STR(string) +
                                                        NUM2LONG(index)));
        }
        default:
                return rb_funcall(other, rb_intern("=~"), 1, self);
        }
}
