#include <ctype.h>

#include "rb_includes.h"
#include "rb_u_buffer.h"

static inline bool
rb_u_string_dump_escape(VALUE buffer, unsigned char c)
{
        const char *escape = NULL;

        switch (c) {
        case '"':       escape = "\\\""; break;
        case '\\':      escape = "\\\\"; break;
        case '\n':      escape = "\\n";  break;
        case '\r':      escape = "\\r";  break;
        case '\t':      escape = "\\t";  break;
        case '\f':      escape = "\\f";  break;
        case '\013':    escape = "\\v";  break;
        case '\010':    escape = "\\v";  break;
        case '\007':    escape = "\\v";  break;
        case '\033':    escape = "\\v";  break;
        default:
                        return false;
        }

        rb_u_buffer_append(buffer, escape, 2);

        return true;
}

#define IS_EVSTR(p,e) ((p) < (e) && (*(p) == '$' || *(p) == '@' || *(p) == '{'))

static inline bool
rb_u_string_dump_hash(VALUE buffer, unsigned char c, const char *p, const char *end)
{
        if (c != '#' || !IS_EVSTR(p, end))
                return false;

        rb_u_buffer_append(buffer, "\\#", 2);

        return true;
}

static inline bool
rb_u_string_dump_ascii_printable(VALUE buffer, unsigned char c)
{
        /* NOTE: This isn’t exactly like Ruby’s definition, since Ruby 1.8
         * doesn’t define isascii correctly. */
        if (!isprint(c))
                return false;

        rb_u_buffer_append_unichar(buffer, c);

        return true;
}

static inline bool
rb_u_string_dump_codepoint(VALUE buffer, const char **p, const char *end)
{
        unichar c = u_aref_char_n(*p, end - *p);

        if (c == UTF_INCOMPLETE_INPUT_UNICHAR ||
            c == UTF_BAD_INPUT_UNICHAR)
                return false;

        char escaped[3 + sizeof(c) * CHAR_BIT + 2 + 1];
        int length = snprintf(escaped, sizeof(escaped), "\\u{%x}", c);
        rb_u_buffer_append(buffer, escaped, length);

        /* -1, since we increase p inside the loop. */
        *p = u_next(*p) - 1;

        return true;
}

static inline void
rb_u_string_dump_hex(VALUE buffer, unsigned char c)
{
        char escaped[4 + 1];
        int length = snprintf(escaped, sizeof(escaped), "\\x%02X", c);
        rb_u_buffer_append(buffer, escaped, length);
}

VALUE
rb_u_string_dump(VALUE self)
{
        const UString *string = RVAL2USTRING(self);
        const char *p = USTRING_STR(string);
        const char *end = USTRING_END(string);

        VALUE buffer = rb_u_buffer_new_sized(7);

        rb_u_buffer_append(buffer, "\"", 1);
        while (p < end) {
                unsigned char c = *p;

                if (!rb_u_string_dump_escape(buffer, c) &&
                    !rb_u_string_dump_hash(buffer, c, p, end) &&
                    !rb_u_string_dump_ascii_printable(buffer, c) &&
                    !rb_u_string_dump_codepoint(buffer, &p, end))
                        rb_u_string_dump_hex(buffer, c);

                p++;
        }
        rb_u_buffer_append(buffer, "\".u", 3);
        
        VALUE result = rb_u_buffer_to_u_bang(buffer);

        OBJ_INFECT(result, self);

        return result;
}
