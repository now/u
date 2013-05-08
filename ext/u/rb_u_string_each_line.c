#include "rb_includes.h"
#include "yield.h"

static void
rb_u_string_each_line_default(VALUE self, struct yield *yield)
{
        const struct rb_u_string *string = RVAL2USTRING(self);

        const char *begin = USTRING_STR(string);
        const char *base = begin;
        const char *p = begin;
        const char *end = USTRING_END(string);

        while (p < end) {
                p = memchr(p, '\n', end - p);
                if (p == NULL)
                        break;
                p++;

                yield_call(yield, rb_u_string_new_c(self, base, p - base));

                base = p;
        }

        if (base != end)
                yield_call(yield, rb_u_string_new_c(self, base, end - base));
}

static void
rb_u_string_each_line_separator(VALUE self, const struct rb_u_string *separator,
                                struct yield *yield)
{
        const struct rb_u_string *string = RVAL2USTRING(self);

        long separator_length = USTRING_LENGTH(separator);
        uint32_t first;
        if (separator_length == 0)
                first = '\n';
        else
                u_decode(&first, USTRING_STR(separator), USTRING_END(separator));

        const char *begin = USTRING_STR(string);
        const char *base = begin;
        const char *p = begin;
        const char *end = USTRING_END(string);

        while (p < end) {
                uint32_t c;
                const char *q = u_decode(&c, p, end);
again:
                if (separator_length == 0 && c == first) {
                        p = q;
                        if (p < end) {
                                q = u_decode(&c, p, end);
                                if (c != first)
                                        goto again;
                        }
                        while (p < end) {
                                uint32_t d;
                                q = u_decode(&d, p, end);
                                if (d != first)
                                        break;
                                p = q;
                        }
                }

                if (c == first &&
                    (separator_length < 2 ||
                     (end - p >= separator_length &&
                      memcmp(USTRING_STR(separator), p, separator_length) == 0))) {
                        p += separator_length;
                        yield_call(yield, rb_u_string_new_c(self, base, p - base));
                        base = p;
                } else
                        p = q;
        }

        if (base != end)
                yield_call(yield, rb_u_string_new_c(self, base, end - base));
}

static void
each(int argc, VALUE *argv, VALUE self, struct yield *yield)
{
        VALUE rs;
        if (argc == 0)
                rs = rb_rs;
        else
                rb_scan_args(argc, argv, "01", &rs);
        if (NIL_P(rs)) {
                yield_call(yield, self);
                return;
        }
        const struct rb_u_string *separator = RVAL2USTRING_ANY(rs);
        if (rs == rb_default_rs)
                rb_u_string_each_line_default(self, yield);
        else
                rb_u_string_each_line_separator(self, separator, yield);
}

/* @overload each_line(separator = $/){ |lp| … }
 *
 *   Enumerates the lines of the receiver, inheriting any taint and untrust.
 *
 *   If SEPARATOR is nil, yields self.  If SEPARATOR is {#empty?}, separates
 *   each line (paragraph) by two or more U+000A LINE FEED characters.
 *
 *   @param [U::String, #to_str] separator
 *   @yieldparam [U::String, self] lp
 *   @return [self]
 *
 * @overload each_line(separator = $/)
 *
 *   Returns an Enumerator over the lines of the receiver.
 *
 *   If SEPARATOR is nil, self will be yielded.  If SEPARATOR is {#empty?},
 *   separates each line (paragraph) by two or more U+000A LINE FEED
 *   characters.
 *
 *   @param [U::String, #to_str] separator
 *   @return [Enumerator] */
VALUE
rb_u_string_each_line(int argc, VALUE *argv, VALUE self)
{
        RETURN_ENUMERATOR(self, argc, argv);
        struct yield y = YIELD_INIT;
        each(argc, argv, self, &y);
        return self;
}

/* @overload lines(separator = $/)
 *
 *   Returns the lines of the receiver, inheriting any taint and untrust.
 *
 *   If SEPARATOR is nil, yields self.  If SEPARATOR is {#empty?}, separates
 *   each line (paragraph) by two or more U+000A LINE FEED characters.
 *
 *   @param [U::String, #to_str] separator
 *   @return [Array<U::String>] */
VALUE
rb_u_string_lines(int argc, VALUE *argv, VALUE self)
{
        struct yield_array y = YIELD_ARRAY_INIT;
        each(argc, argv, self, &y.yield);
        return y.array;
}
