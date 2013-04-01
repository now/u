#include "rb_includes.h"

long
rb_u_string_rindex(VALUE self, VALUE rbsubstring, long offset)
{
        const struct rb_u_string *string = RVAL2USTRING(self);
        const struct rb_u_string *substring = RVAL2USTRING_ANY(rbsubstring);

        if (USTRING_LENGTH(string) < USTRING_LENGTH(substring))
                return -1;

        const char *s = rb_u_string_begin_from_offset(string, offset);
        if (s == NULL)
                return -1;

        if (USTRING_LENGTH(substring) == 0)
                return offset;

        const char *begin = USTRING_STR(string);
        const char *t = USTRING_STR(substring);
        long t_length = USTRING_LENGTH(substring);
        while (s >= begin) {
                if (rb_memcmp(s, t, t_length) == 0)
                        return u_pointer_to_offset(begin, s);
                s--;
        }

        return -1;
}

/* @overload rindex(pattern, offset = -1)
 *
 *   Returns the maximal index of the receiver where PATTERN matches, equal to
 *   or less than _i_, where _i_ = OFFSET if OFFSET ≥ 0, _i_ = {#length} -
 *   abs(OFFSET) otherwise, or nil if there is no match.
 *
 *   If PATTERN is a Regexp, the Regexp special variables `$&`, `$'`,
 *   <code>$\`</code>, `$1`, `$2`, …, `$`_n_ are updated accordingly.
 *
 *   If PATTERN responds to `#to_str`, the matching is performed by a byte
 *   comparison.
 *
 *   @param [Regexp, #to_str] pattern
 *   @param [#to_int] offset
 *   @return [Integer, nil]
 *   @see #index */
VALUE
rb_u_string_rindex_m(int argc, VALUE *argv, VALUE self)
{
        const struct rb_u_string *string = RVAL2USTRING(self);

        VALUE sub, rboffset;
        long offset;
        if (rb_scan_args(argc, argv, "11", &sub, &rboffset) == 2)
                offset = NUM2LONG(rboffset);
        else
                /* TODO: Why not simply use -1?  Benchmark which is faster. */
                offset = u_length_n(USTRING_STR(string), USTRING_LENGTH(string));

        const char *begin = rb_u_string_begin_from_offset(string, offset);
        const char *end = USTRING_END(string);
        if (begin == NULL) {
                if (offset <= 0) {
                        if (TYPE(sub) == T_REGEXP)
                                rb_backref_set(Qnil);

                        return Qnil;
                }

                begin = end;
                /* TODO: this converting back and forward can be optimized away
                 * if rb_u_string_index_regexp() and rb_u_string_rindex() were split up
                 * into two additional functions, adding
                 * rb_u_string_index_regexp_pointer() and rb_u_string_rindex_pointer(),
                 * so that one can pass a pointer to start at immediately
                 * instead of an offset that gets calculated into a pointer. */
                offset = u_length_n(USTRING_STR(string), USTRING_LENGTH(string));
        }

        /* TODO: Adjust this to be able to deal with struct rb_u_string in a fast way as
         * well. */
        switch (TYPE(sub)) {
        case T_REGEXP:
                /* TODO: What’s this first test for, exactly? */
                if (RREGEXP(sub)->ptr == NULL || RREGEXP_SRC_LEN(sub) > 0)
                        offset = rb_u_string_index_regexp(self, begin, sub, true);
                break;
        default: {
                VALUE tmp = rb_check_string_type(sub);
                if (NIL_P(tmp))
                        rb_u_raise(rb_eTypeError, "type mismatch: %s given",
                                   rb_obj_classname(sub));

                sub = tmp;
        }
                /* fall through */
        case T_STRING:
                offset = rb_u_string_rindex(self, sub, offset);
                break;
        }

        if (offset < 0)
                return Qnil;

        return LONG2NUM(offset);
}
