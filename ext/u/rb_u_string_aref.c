#include "rb_includes.h"
#include "rb_u_re.h"

static VALUE
rb_u_string_substr_impl(VALUE self, long offset, long len, bool nil_on_empty)
{
        if (len < 0)
                return Qnil;

        const UString *string = RVAL2USTRING(self);

        const char *begin = rb_u_string_begin_from_offset(string, offset);
        if (begin == NULL)
                return Qnil;

        const char *end = u_offset_to_pointer_n(begin, len, USTRING_END(string) - begin);
        if (end == NULL)
                end = USTRING_END(string);

        if (nil_on_empty && begin == end)
                return Qnil;

        if (begin == USTRING_STR(string) && end == USTRING_END(string))
                return self;

        VALUE substr = rb_u_string_new(begin, end - begin);

        OBJ_INFECT(substr, self);

        return substr;
}

VALUE
rb_u_string_substr(VALUE self, long offset, long len)
{
        return rb_u_string_substr_impl(self, offset, len, false);
}

static VALUE
rb_u_string_subpat(VALUE self, VALUE re, VALUE reference)
{
        if (rb_reg_search(re, StringValue(self), 0, 0) < 0)
                return Qnil;

        VALUE match = rb_u_pattern_match_reference(reference);

        /* TODO: If this pattern appears in the future, add
         * rb_u_string_new_rb_nilable. */
        return NIL_P(match) ? Qnil : rb_u_string_new_rb(match);
}

static VALUE
rb_u_string_aref_num(VALUE self, long offset)
{
        return rb_u_string_substr_impl(self, offset, 1, true);
}

static VALUE
rb_u_string_aref_default(VALUE self, VALUE index)
{
        const UString *string = RVAL2USTRING(self);
        long n_chars = u_length_n(USTRING_STR(string), USTRING_LENGTH(string));

        long begin, length;
        switch (rb_range_beg_len(index, &begin, &length, n_chars, 0)) {
        case Qfalse:
                return rb_u_string_aref_num(self, NUM2LONG(index));
        case Qnil:
                return Qnil;
        default:
                return rb_u_string_substr(self, begin, length);
        }
}

static VALUE
rb_u_string_aref(VALUE self, VALUE index)
{
        if (TYPE(index) == T_STRING || rb_obj_is_kind_of(index, rb_cUString)) {
                if (rb_u_string_index(self, index, 0) == -1)
                        return Qnil;

                /* TODO: Why not simply return index if it is a U::String? */
                return TYPE(index) == T_STRING ?
                        rb_u_string_new(RSTRING_PTR(index), RSTRING_LEN(index)) :
                        rb_u_string_dup(index);
        }

        switch (TYPE(index)) {
        case T_FIXNUM:
                return rb_u_string_aref_num(self, FIX2LONG(index));
        case T_REGEXP:
                return rb_u_string_subpat(self, index, INT2FIX(0));
        default:
                return rb_u_string_aref_default(self, index);
        }
}

/* @overload [](index)
 *
 *   Extracts the substring [max(_i_, 0), min({#length}, _i_ + 1)], where _i_ =
 *   _index_ if _index_ ≥ 0, _i_ = {#length} - abs(_index_) otherwise.
 *
 *   Any taint or untrust is inherited by the substring.
 *
 *   @param [Integer] index Index to begin at
 *   @return [U::String, nil] The extracted substring, or nil if the resulting
 *     substring is empty
 *
 * @overload [](index, length)
 *
 *   Extracts the substring [max(_i_, 0), min({#length}, _i_ + _length_)],
 *   where _i_ = _index_ if _index_ ≥ 0, _i_ = {#length} - abs(_index_)
 *   otherwise.
 *
 *   Any taint or untrust is inherited by the substring.
 *
 *   @param [Integer] index Index to begin at
 *   @param [Integer] length Number of characters to extract
 *   @return [U::String, nil] The extracted substring, or nil if _length_ < 0
 *
 * @overload [](range)
 *
 *   Same as `self[i, j - k]`, where _i_ = _range_`.begin` if _range_`.begin` ≥
 *   0, _i_ = {#length} - abs(_range_`.begin`) otherwise, _j_ = _range_`.end`
 *   if _range_`.end` ≥ 0, _j_ = {#length} - abs(_range_`.end`) otherwise, and
 *   _k_ = 1 if _range_`.exclude_end?`, _k_ = 0 otherwise.
 *
 *   @param [Range] range Range to extract
 *   @return [U::String, nil] The extracted substring, or nil if _j_ - _k_ < 0
 *
 * @overload [](regexp, reference = 0)
 *
 *   Extracts the submatch _reference_ from the match of _regexp_ in `self`.
 *
 *   Any taint or untrust is inherited by the submatch.
 *
 *   @param [Regexp] regexp Regexp to match against `self`
 *   @param [Integer, String, Symbol] reference Number or name of submatch to
 *     extract
 *   @raise [IndexError] If _reference_ doesn’t refer to a submatch
 *   @return [U::String, nil] The extracted submatch, or nil if no match was
 *     found or if the submatch wasn’t a part of the overall match
 *
 * @overload [](string)
 *
 *   Returns _string_ if it is a substring of `self`.
 *
 *   Any taint or untrust is inherited by the returned substring.
 *
 *   @param [U::String, String] string Substring to match against `self`
 *   @return [U::String, nil] The substring of `self` equal to _string_, or nil
 *     if it didn’t match
 *
 * @overload [](object)
 *
 *   Returns `nil` for any object that isn’t any of the classes already listed.
 *
 *   @param [Object] Any object
 *   @return [nil] nil */
VALUE
rb_u_string_aref_m(int argc, VALUE *argv, VALUE self)
{
        need_m_to_n_arguments(argc, 1, 2);

        if (argc == 1)
                return rb_u_string_aref(self, argv[0]);

        if (TYPE(argv[0]) == T_REGEXP)
                return rb_u_string_subpat(self, argv[0], argv[1]);

        return rb_u_string_substr(self, NUM2LONG(argv[0]), NUM2LONG(argv[1]));
}
