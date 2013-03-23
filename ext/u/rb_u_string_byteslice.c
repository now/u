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

/* @overload byteslice(index)
 *   @param [Integer] index
 *   @return [U::String, nil] The byte-index-based substring [max(_i_, 0),
 *     min({#bytesize}, _i_ + 1)], where _i_ = INDEX if INDEX ≥ 0, _i_ =
 *     {#bytesize} - abs(INDEX) otherwise, inheriting any taint or untrust, or
 *     nil if this substring is empty
 *
 * @overload byteslice(index, length)
 *   @param [Integer] index
 *   @param [Integer] length
 *   @return [U::String, nil] The byte-index-based substring [max(_i_, 0),
 *     min({#bytesize}, _i_ + LENGTH)], where _i_ = INDEX if INDEX ≥ 0, _i_ =
 *     {#bytesize} - abs(INDEX) otherwise, inheriting any taint or untrust, or
 *     nil if LENGTH < 0
 *
 * @overload byteslice(range)
 *   @param [Range] range
 *   @return [U::String, nil] The result of `#[i, j - k]`, where _i_ =
 *     RANGE#begin if RANGE#begin ≥ 0, _i_ = {#bytesize} - abs(RANGE#begin)
 *     otherwise, _j_ = RANGE#end if RANGE#end ≥ 0, _j_ = {#bytesize} -
 *     abs(RANGE#end) otherwise, and _k_ = 1 if RANGE#exclude_end?, _k_ = 0
 *     otherwise, or nil if _j_ - _k_ < 0
 *
 * @overload byteslice(object)
 *   @param [Object] object
 *   @return [nil] Nil for any object that doesn’t satisfy the other cases */
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
