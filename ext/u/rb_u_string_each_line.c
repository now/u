#include "rb_includes.h"

static VALUE
rb_u_string_each_line_default(VALUE self)
{
        const UString *string = RVAL2USTRING(self);

        const char *begin = USTRING_STR(string);
        const char *base = begin;
        const char *p = begin;
        const char *end = USTRING_END(string);

        while (p < end) {
                p = memchr(p, '\n', end - p);
                if (p == NULL)
                        break;
                p++;

                VALUE line = rb_u_string_new(base, p - base);
                OBJ_INFECT(line, self);
                rb_yield(line);

                base = p;
        }

        if (base != end) {
                VALUE line = rb_u_string_new(base, end - base);
                OBJ_INFECT(line, self);
                rb_yield(line);
        }

        return self;
}

static VALUE
rb_u_string_each_line_separator(VALUE self, const UString *separator)
{
        const UString *string = RVAL2USTRING(self);

        long separator_length = USTRING_LENGTH(separator);
        unichar first = (separator_length == 0) ?
                '\n' : _rb_u_aref_char_validated(USTRING_STR(separator), USTRING_END(separator));

        const char *begin = USTRING_STR(string);
        const char *base = begin;
        const char *p = begin;
        const char *end = USTRING_END(string);

        while (p < end) {
                unichar c = _rb_u_aref_char_validated(p, end);

again:
                if (separator_length == 0 && c == first) {
                        p = u_next(p);
                        if (p < end) {
                                c = _rb_u_aref_char_validated(p, end);

                                if (c != first)
                                        goto again;
                        }
                        while (p < end) {
                                if (_rb_u_aref_char_validated(p, end) != first)
                                        break;

                                p = u_next(p);
                        }
                }

                if (c == first &&
                    (separator_length < 2 ||
                     (end - p >= separator_length &&
                      memcmp(USTRING_STR(separator), p, separator_length) == 0))) {
                        p += separator_length;
                        VALUE line = rb_u_string_new(base, p - base);
                        OBJ_INFECT(line, self);
                        rb_yield(line);
                        base = p;
                } else
                        p = u_next(p);
        }

        if (base != end) {
                VALUE line = rb_u_string_new(base, end - base);
                OBJ_INFECT(line, self);
                rb_yield(line);
        }

        return self;
}

/* @overload each_line(separator = $/){ |line| … }
 *
 *   Enumerate each line in this {U::String}.  If _separator_ is nil, yields
 *   `self`.  If _separator_ is {#empty?}, separates each line (paragraph) by
 *   two or more U+000A LINE FEED characters.
 *
 *   @param [U::String, #to_str] separator Line separator to use
 *   @yield [line] Enumerate each line in this {U::String}
 *   @yieldparam [Integer] line Line at current position
 *   @return [U::String] `self`
 *
 * @overload each_line(separator = $/)
 *
 *   Creates an Enumerator over each codepoint in this {U::String}.  If
 *   _separator_ is `nil`, `self` will be yielded.  If _separator_ is
 *   {#empty?}, separates each line (paragraph) by two or more U+000A LINE FEED
 *   characters.
 *
 *   @param [U::String, #to_str] separator Line separator to use
 *   @yield [line] Enumerate each line in this {U::String}
 *   @return [Enumerator] An Enumerator over each line in this {U::String}
 */
VALUE
rb_u_string_each_line(int argc, VALUE *argv, VALUE self)
{
        RETURN_ENUMERATOR(self, argc, argv);

        VALUE rs;
        if (argc == 0)
                rs = rb_rs;
        else
                rb_scan_args(argc, argv, "01", &rs);
        if (NIL_P(rs)) {
                rb_yield(self);
                return self;
        }

        const UString *separator = RVAL2USTRING_ANY(rs);
        if (rs == rb_default_rs)
                return rb_u_string_each_line_default(self);

        return rb_u_string_each_line_separator(self, separator);
}
