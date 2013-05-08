#include "rb_includes.h"

static VALUE
rb_u_string_chomp_default(VALUE self)
{
        const struct rb_u_string *string = RVAL2USTRING(self);

        const char *begin = USTRING_STR(string);
        const char *end = USTRING_END(string);

        const char *last = u_find_prev(begin, end);
        if (last == NULL)
                return self;

        const char *q;
        uint32_t c = u_decode(&q, last, end);
        if (c == '\n') {
                const char *last_but_one = u_find_prev(begin, last);

                if (last_but_one != NULL && *last_but_one == '\r')
                        last = last_but_one;
        } else if (!u_char_isnewline(c))
                return self;

        return rb_u_string_new_c(self, begin, last - begin);
}

static VALUE
rb_u_string_chomp_newlines(VALUE self)
{
        const struct rb_u_string *string = RVAL2USTRING(self);
        const char *begin = USTRING_STR(string);
        const char *end = USTRING_END(string);

        const char *last = end;
        while (last > begin) {
                const char *last_but_one = u_find_prev(begin, last);
                if (last_but_one == NULL)
                        break;
                const char *q;
                if (!u_char_isnewline(u_decode(&q, last_but_one, end)))
                        break;
                last = last_but_one;
        }

        if (last == end)
                return self;

        return rb_u_string_new_c(self, begin, last - begin);
}

/* @overload chomp(separator = $/)
 *
 *   Returns the receiver, minus any SEPARATOR suffix, inheriting any taint and
 *   untrust, unless {#length} = 0, in which case nil is returned.  If
 *   SEPARATOR is nil or invalidly encoded, the receiver is returned.
 *
 *   If SEPARATOR is `$/` and `$/` has its default value or if SEPARATOR is
 *   U+000A LINE FEED, the longest suffix consisting of any of
 *
 *   * U+000A LINE FEED
 *   * U+000D CARRIAGE RETURN
 *   * U+000D CARRIAGE RETURN, U+000D LINE FEED
 *
 *   will be removed. If no such suffix exists and the last character is a
 *   {#newline?}, it will be removed instead.
 *
 *   If SEPARATOR is {#empty?}, remove the longest {#newline?} suffix.
 *
 *   @param [U::String, #to_str, nil] separator
 *   @return [U::String, self, nil]
 *   @see #chop
 *   @see #lstrip
 *   @see #rstrip
 *   @see #strip */
VALUE
rb_u_string_chomp(int argc, VALUE *argv, VALUE self)
{
        const struct rb_u_string *string = RVAL2USTRING(self);

        long length = USTRING_LENGTH(string);
        if (length == 0)
                return Qnil;

        VALUE rs;
        if (argc == 0) {
                rs = rb_rs;
                if (rs == rb_default_rs)
                        return rb_u_string_chomp_default(self);
        } else {
                rb_scan_args(argc, argv, "01", &rs);
        }
        if (NIL_P(rs))
                return self;

        const struct rb_u_string *separator = RVAL2USTRING_ANY(rs);

        long separator_length = USTRING_LENGTH(separator);
        if (separator_length == 0)
                return rb_u_string_chomp_newlines(self);

        if (separator_length > length)
                return self;

        char last_char = USTRING_STR(separator)[separator_length - 1];
        if (separator_length == 1 && last_char == '\n')
                return rb_u_string_chomp_default(self);

        if (!u_isvalid_n(USTRING_STR(separator), separator_length, NULL) ||
            USTRING_STR(string)[length - 1] != last_char ||
            (separator_length > 1 &&
             rb_memcmp(USTRING_STR(separator),
                       USTRING_END(string) - separator_length,
                       separator_length) != 0))
                return self;

        return rb_u_string_new_c(self, USTRING_STR(string), length - separator_length);
}
