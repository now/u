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
        case '\010':    escape = "\\b";  break;
        case '\007':    escape = "\\a";  break;
        case '\033':    escape = "\\e";  break;
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
        if (c != '#' || !IS_EVSTR(p + 1, end))
                return false;

        rb_u_buffer_append(buffer, "\\#", 2);

        return true;
}

static inline bool
rb_u_string_dump_ascii_printable(VALUE buffer, unsigned char c)
{
        if (c > 0x7f || !unichar_isprint(c))
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

/* Dumps this {U::String} into a reader-friendly format.
 *
 * The first character is `"`.  Then, any {#printable?} characters in the ASCII
 * range are output as-is.  The following special characters are escaped in the
 * output:
 *
 * <table>
 *   <tr><td>Character</td><td>Dumped Sequence</td></tr>
 *   <tr><td>U+0022 QUOTATION MARK</td><td><code>\"</code></td></tr>
 *   <tr><td>U+005C REVERSE SOLIDUS</td><td><code>\\</code></td></tr>
 *   <tr><td>U+000A LINE FEED (LF)</td><td><code>\n</code></td></tr>
 *   <tr><td>U+000D CARRIAGE RETURN (CR)</td><td><code>\r</code></td></tr>
 *   <tr><td>U+0009 CHARACTER TABULATION</td><td><code>\t</code></td></tr>
 *   <tr><td>U+000C FORM FEED (FF)</td><td><code>\f</code></td></tr>
 *   <tr><td>U+000B LINE TABULATION</td><td><code>\v</code></td></tr>
 *   <tr><td>U+0008 BACKSPACE</td><td><code>\b</code></td></tr>
 *   <tr><td>U+0007 BELL</td><td><code>\a</code></td></tr>
 *   <tr><td>U+001B ESCAPE</td><td><code>\e</code></td></tr>
 * </table>
 *
 * The following special sequences are also escaped:
 *
 * <table>
 *   <tr><td>Sequence</td><td>Dumped Sequence</td></tr>
 *   <tr><td><code>#$</code></td><td><code>\#$</code></td></tr>
 *   <tr><td><code>#@</code></td><td><code>\#@</code></td></tr>
 *   <tr><td><code>#{</code></td><td><code>\#{</code></td></tr>
 * </table>
 *
 * Valid UTF-8 byte sequences are output as `\u{`_n_`}`, where _n_ is the
 * lowercase hexadecimal representation of the codepoint encoded by the UTF-8
 * sequence.
 *
 * Any other byte is output as `\x`_n_, where _n_ is the two-digit uppercase
 * hexadecimal representation of the byte’s value.
 *
 * The result is terminated with `".u`.
 *
 * Any untrust or taint is inherited by the result.
 *
 * @return [U::String] A reader-friendly version of this {U::String} */
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
