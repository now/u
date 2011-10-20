#include "rb_includes.h"

/* Removes the last character in `self`.
 *
 * If the last character is U+000A LINE FEED and the second-to-last character
 * is U+000D CARRIAGE RETURN, both characters are removed.
 *
 * If `self` is {#empty?} or if the last character of `self` is invalidly
 * encoded, no character is removed.
 *
 * @return [U::String] `self` with the last character removed
 *
 * @see #chomp
 * @see #lstrip
 * @see #rstrip
 * @see #strip */
VALUE
rb_u_string_chop(VALUE self)
{
        const UString *string = RVAL2USTRING(self);

        if (USTRING_LENGTH(string) == 0)
                return self;

        const char *begin = USTRING_STR(string);
        const char *end = USTRING_END(string);

        const char *last = u_find_prev(begin, end);
        if (last == NULL)
                return self;

        if (_rb_u_aref_char_validated(last, end) == '\n') {
                const char *last_but_one = u_find_prev(begin, last);

                /* TODO: Can use *last_but_one here. */
                if (last_but_one != NULL && u_aref_char(last_but_one) == '\r')
                        last = last_but_one;
        }

        return rb_u_string_new(begin, last - begin);
}
