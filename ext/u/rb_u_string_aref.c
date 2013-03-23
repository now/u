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
 *   @param [Integer] index
 *   @return [U::String, nil] The substring [max(_i_, 0), min({#length}, _i_ +
 *     1)], where _i_ = INDEX if INDEX ≥ 0, _i_ = {#length} - abs(INDEX)
 *     otherwise, inheriting any taint or untrust, or nil if this substring is
 *     empty
 *
 * @overload [](index, length)
 *   @param [Integer] index
 *   @param [Integer] length
 *   @return [U::String, nil] The substring [max(_i_, 0), min({#length}, _i_ +
 *     LENGTH)], where _i_ = INDEX if INDEX ≥ 0, _i_ = {#length} - abs(INDEX)
 *     otherwise, inheriting any taint or untrust, or nil if LENGTH < 0
 *
 * @overload [](range)
 *   @param [Range] range
 *   @return [U::String, nil] The result of `#[i, j - k]`, where _i_ =
 *     RANGE#begin if RANGE#begin ≥ 0, _i_ = {#length} - abs(RANGE#begin)
 *     otherwise, _j_ = RANGE#end if RANGE#end ≥ 0, _j_ = {#length} -
 *     abs(RANGE#end) otherwise, and _k_ = 1 if RANGE#exclude_end?, _k_ = 0
 *     otherwise, or nil if _j_ - _k_ < 0
 *
 * @overload [](regexp, reference = 0)
 *   @param [Regexp] regexp
 *   @param [Integer, #to_str, Symbol] reference
 *   @raise [IndexError] If REFERENCE doesn’t refer to a submatch
 *   @return [U::String, nil] The submatch REFERENCE from the first match of
 *     REGEXP in the receiver, inheriting any taint and untrust, or nil if
 *     there is no match or if the submatch isn’t part of the overall match
 *
 * @overload [](string)
 *   @param [U::String, ::String] string
 *   @return [U::String, nil] The substring STRING of the receiver, inheriting
 *     any taint and untrust, if STRING is a substring of the receiver
 *
 * @overload [](object)
 *   @param [Object] object
 *   @return [nil] Nil for any object that doesn’t satisfy the other cases */
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
