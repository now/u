#include "rb_includes.h"

static VALUE
rb_u_string_byte_substr(VALUE self, long offset, long length)
{
        const UString *string = RVAL2USTRING(self);
        long n = USTRING_LENGTH(string);

        if (offset > n || length < 0)
                return Qnil;

        if (offset < 0) {
                offset += n;
                if (offset < 0)
                        return Qnil;
        }

        if (offset + length > n)
                length = n - offset;

        if (length <= 0)
                return rb_u_string_new_empty(self);

        return rb_u_string_new_subsequence(self, offset, length);
}

static VALUE
rb_u_string_byteslice_num(VALUE self, long offset)
{
        VALUE result = rb_u_string_byte_substr(self, offset, 1);

        if (NIL_P(result) || USTRING_LENGTH(RVAL2USTRING(result)) == 0)
                return Qnil;

        return result;
}

static VALUE
rb_u_string_byteslice_default(VALUE self, VALUE index)
{
        const UString *string = RVAL2USTRING(self);
        long n_bytes = USTRING_LENGTH(string);

        long begin, length;
        switch (rb_range_beg_len(index, &begin, &length, n_bytes, 0)) {
        case Qfalse:
                return rb_u_string_byteslice_num(self, NUM2LONG(index));
        case Qnil:
                return Qnil;
        default:
                return rb_u_string_byte_substr(self, begin, length);
        }
}

static VALUE
rb_u_string_byteslice(VALUE self, VALUE index)
{
        switch (TYPE(index)) {
        case T_FIXNUM:
                return rb_u_string_byteslice_num(self, FIX2LONG(index));
        default:
                return rb_u_string_byteslice_default(self, index);
        }
}

VALUE
rb_u_string_byteslice_m(int argc, VALUE *argv, VALUE self)
{
        need_m_to_n_arguments(argc, 1, 2);

        if (argc == 1)
                return rb_u_string_byteslice(self, argv[0]);

        return rb_u_string_byte_substr(self,
                                       NUM2LONG(argv[0]),
                                       NUM2LONG(argv[1]));
}
