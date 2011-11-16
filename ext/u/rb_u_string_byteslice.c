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
 *
 *   Extracts the substring [max(_i_, 0), min({#length}, _i_ + 1)], where _i_ =
 *   _index_ if _index_ ≥ 0, _i_ = {#length} - abs(_index_) otherwise.  Note
 *   that these are byte indexes, not character indexes.
 *
 *   Any taint or untrust is inherited by the substring.
 *
 *   @param [Integer] index Index to begin at
 *   @return [U::String, nil] The extracted substring, or nil if the resulting
 *     substring is empty
 *
 * @overload byteslice(index, length)
 *
 *   Extracts the substring [max(_i_, 0), min({#length}, _i_ + _length_)],
 *   where _i_ = _index_ if _index_ ≥ 0, _i_ = {#length} - abs(_index_)
 *   otherwise. Note that these are byte indexes, not character indexes.
 *
 *   Any taint or untrust is inherited by the substring.
 *
 *   @param [Integer] index Index to begin at
 *   @param [Integer] length Number of bytes to extract
 *   @return [U::String, nil] The extracted substring, or nil if _length_ < 0
 *
 * @overload byteslice(range)
 *
 *   Same as `self[i, j - k]`, where _i_ = _range_`.begin` if _range_`.begin` ≥
 *   0, _i_ = {#length} - abs(_range_`.begin`) otherwise, _j_ = _range_`.end`
 *   if _range_`.end` ≥ 0, _j_ = {#length} - abs(_range_`.end`) otherwise, and
 *   _k_ = 1 if _range_`.exclude_end?`, _k_ = 0 otherwise. Note that these are
 *   byte indexes, not character indexes.
 *
 *   @param [Range] range Range to extract
 *   @return [U::String, nil] The extracted substring, or nil if _j_ - _k_ < 0
 *
 * @overload byteslice(object)
 *
 *   Returns `nil` for any object that isn’t any of the classes already listed.
 *
 *   @param [Object] object Any object
 *   @return [nil] nil */
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
