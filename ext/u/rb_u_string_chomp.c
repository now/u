#include "rb_includes.h"

static VALUE
rb_u_string_chomp_default(VALUE self)
{
        const UString *string = RVAL2USTRING(self);

        const char *begin = USTRING_STR(string);
        const char *end = USTRING_END(string);

        const char *last = u_find_prev(begin, end);
        if (last == NULL)
                return self;

        if (_rb_u_aref_char_validated(last, end) == '\n') {
                const char *last_but_one = u_find_prev(begin, last);

                /* TODO: We can use *last_but_one here. */
                if (last_but_one != NULL && u_aref_char(last_but_one) == '\r')
                        last = last_but_one;
        } else if (!unichar_isnewline(u_aref_char(last))) {
                return self;
        }

        return rb_u_string_new(begin, last - begin);
}

static VALUE
rb_u_string_chomp_newlines(VALUE self)
{
        const UString *string = RVAL2USTRING(self);
        const char *begin = USTRING_STR(string);
        const char *end = USTRING_END(string);

        const char *last = end;
        while (last > begin) {
                const char *last_but_one = u_find_prev(begin, last);
                if (last == NULL || !unichar_isnewline(u_aref_char(last_but_one)))
                        break;
                last = last_but_one;
        }

        if (last == end)
                return self;

        return rb_u_string_new(begin, last - begin);
}

VALUE
rb_u_string_chomp(int argc, VALUE *argv, VALUE self)
{
        const UString *string = RVAL2USTRING(self);

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

        const UString *separator = RVAL2USTRING_ANY(rs);

        long separator_length = USTRING_LENGTH(separator);
        if (separator_length == 0)
                return rb_u_string_chomp_newlines(self);

        if (separator_length > length)
                return self;

        char last_char = USTRING_STR(separator)[separator_length - 1];
        if (separator_length == 1 && last_char == '\n')
                return rb_u_string_chomp_default(self);

        if (!utf_isvalid_n(USTRING_STR(separator), separator_length, NULL) ||
            USTRING_STR(string)[length - 1] != last_char ||
            (separator_length > 1 &&
             rb_memcmp(USTRING_STR(separator),
                       USTRING_END(string) - separator_length,
                       separator_length) != 0))
                return self;

        /* TODO: It would be nice to share the underlying char * in this case.
         * This would require reference counting. Call the function
         * rb_u_string_new_ref(). */
        return rb_u_string_new(USTRING_STR(string), length - separator_length);
}
