#include "rb_includes.h"

VALUE
rb_u_insert(VALUE str, VALUE index, VALUE other)
{
        StringValue(str);
        long offset = NUM2LONG(index);

        long n_chars = u_length_n(RSTRING(str)->ptr, RSTRING(str)->len);
        /*
        char *begin, *end;
        if (offset < 0)
                offset++;
        rb_u_begin_from_offset_validated(str, offset, &begin, &end);
        puts(begin);
        rb_str_update(str, begin - RSTRING(str)->ptr, 0, other);
        */
        if (abs(offset) > n_chars) {
                if (offset < 0)
                        offset += n_chars;
                rb_raise(rb_eIndexError, "index %ld out of string", offset);
        }

        long byte_index;

        if (offset == -1) {
                byte_index = RSTRING(str)->len;
        } else {
                if (offset < 0)
                        offset++;

                char *s = RSTRING(str)->ptr;

                if (offset < 0)
                        s += RSTRING(str)->len;
                byte_index = u_offset_to_pointer(s, offset) - s;
        }

        rb_str_update(str, byte_index, 0, other);

        return str;
}
