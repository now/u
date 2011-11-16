#include "rb_includes.h"
#include "rb_u_re.h"

/* TODO: Return VALUE. */
long
rb_u_string_index_regexp(VALUE self, const char *begin, VALUE regex, bool reverse)
{
        const UString *string = RVAL2USTRING(self);
        VALUE rbstring = rb_str_to_str(self);

        const char *base = USTRING_STR(string);

        long index = rb_reg_search(regex, rbstring,
                                   rb_reg_adjust_startpos(regex, rbstring,
                                                          begin - base,
                                                          reverse),
                                   reverse);
        if (index == -1)
                return -1;

        return u_pointer_to_offset(base, base + index);
}

/* TODO: Return VALUE. */
long
rb_u_string_index(VALUE self, VALUE rbsubstring, long offset)
{
        const UString *string = RVAL2USTRING(self);
        const UString *substring = RVAL2USTRING_ANY(rbsubstring);

        const char *begin = rb_u_string_begin_from_offset(string, offset);
        if (begin == NULL)
                return -1;

        const char *end = USTRING_END(string);

        long substring_length = USTRING_LENGTH(substring);
        if (end - begin < substring_length)
                return -1;
        if (substring_length == 0)
                return offset;

        /* TODO: Should we really be using rb_memsearch?  Why not something
         * more Unicodey? */
        long index = rb_u_memsearch(USTRING_STR(substring), substring_length,
                                    begin,
                                    end - begin);
        if (index < 0)
                return -1;

        return offset + u_pointer_to_offset(begin, begin + index);
}

/* @overload index(pattern, offset = 0)
 *
 *   Finds the minimal index into `self` where _pattern_ matches, equal to or
 *   greater than _i_, where _i_ = _offset_ if _offset_ ≥ 0, _i_ = {#length} -
 *   abs(_offset_) otherwise.
 *
 *   If _pattern_ is a Regexp, the Regexp special variables `$&`, `$'`,
 *   <code>$\`</code>, `$1`, `$2`, …, `$`_n_ are updated accordingly.
 *
 *   If _pattern_ responds to `#to_str`, the matching is performed by a byte
 *   comparison.
 *
 *   @param [Regexp, #to_str] pattern Pattern to search for
 *   @param [Integer] offset Index to start search at
 *   @return [Integer, nil] Index of first match of _pattern_ starting at
 *     _offset_, or `nil` if there is no match
 *   @see #rindex */
VALUE
rb_u_string_index_m(int argc, VALUE *argv, VALUE self)
{
        VALUE sub, rboffset;
        long offset = 0;
        if (rb_scan_args(argc, argv, "11", &sub, &rboffset) == 2)
                offset = NUM2LONG(rboffset);

        const UString *string = RVAL2USTRING(self);

        const char *begin = rb_u_string_begin_from_offset(string, offset);
        if (begin == NULL) {
                if (TYPE(sub) == T_REGEXP)
                        rb_backref_set(Qnil);

                return Qnil;
        }

        /* TODO: Adjust this to be able to deal with UString in a fast way as
         * well. */
        switch (TYPE(sub)) {
        case T_REGEXP:
                offset = rb_u_string_index_regexp(self, begin, sub, false);
                break;
        default: {
                VALUE tmp = rb_check_string_type(sub);
                if (NIL_P(tmp))
                        rb_raise(rb_eTypeError, "type mismatch: %s given",
                                 rb_obj_classname(sub));

                sub = tmp;
        }
                /* fall through */
        case T_STRING:
                offset = rb_u_string_index(self, sub, offset);
                break;
        }

        if (offset < 0)
                return Qnil;

        return LONG2NUM(offset);
}
