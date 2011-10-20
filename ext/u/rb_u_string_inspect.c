#include "rb_includes.h"

static const char *
rb_u_string_inspect_bad_input(const char *p, const char *end, VALUE result)
{
        const char *next = u_find_next(p, end);
        if (next == NULL)
                next = end;
        while (p < next) {
                char hex[5];

                snprintf(hex, lengthof(hex), "\\x%02X", *p & 0xff);
                rb_str_buf_cat2(result, hex);
                p++;
        }

        return next;
}

static void
rb_u_string_inspect_special_char(unichar c, VALUE result)
{
        char str[MAX_UNICHAR_BYTE_LENGTH];

        rb_str_buf_cat2(result, "\\");
        rb_str_buf_cat(result, str, unichar_to_u(c, str));
}

static const char *
rb_u_string_inspect_hash_char(const char *p, const char *end, VALUE result)
{
        const char *next = u_next(p);

        if (next == end) {
                rb_str_buf_cat2(result, "#");
                return end;
        }

        unichar c = u_aref_char(next);
        switch (c) {
        case UTF_BAD_INPUT_UNICHAR:
                rb_str_buf_cat2(result, "#");
                return rb_u_string_inspect_bad_input(p, end, result);
        case '$':
        case '@':
        case '{':
                rb_str_buf_cat2(result, "\\#");
                return next;
        default:
                rb_str_buf_cat2(result, "#");
                return next;
        }
}

static void
rb_u_string_inspect_escaped_char(unichar c, VALUE result)
{
        char str[4 + 8 + 1];

        if (c < 0x10000)
                snprintf(str, lengthof(str), "\\u%04X", c);
        else
                snprintf(str, lengthof(str), "\\u{%X}", c & 0xffffffff);

        rb_str_buf_cat2(result, str);
}

static void
rb_u_string_inspect_default(unichar c, VALUE result)
{
        if (!unichar_isprint(c)) {
                rb_u_string_inspect_escaped_char(c, result);
                return;
        }

        char str[MAX_UNICHAR_BYTE_LENGTH];
        rb_str_buf_cat(result, str, unichar_to_u(c, str));
}

/* Inspects the contents of this {U::String} in a reader-friendly format.
 *
 * The first character is `"`.  Then, the following conversions are performed
 * for the bytes in the string.
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
 * <table>
 *   <tr><td>Sequence</td><td>Dumped Sequence</td></tr>
 *   <tr><td><code>#$</code></td><td><code>\#$</code></td></tr>
 *   <tr><td><code>#@</code></td><td><code>\#@</code></td></tr>
 *   <tr><td><code>#{</code></td><td><code>\#{</code></td></tr>
 * </table>
 *
 * {#printable?} bytes in the ASCII range are output as-is.
 *
 * Valid UTF-8 byte sequences representing codepoints < 0x10000 are output as
 * `\u`_n_, where _n_ is the four-digit uppercase hexadecimal representation
 * of the codepoint.
 *
 * Valid UTF-8 byte sequences representing codepoints ≥ 0x10000 are output as
 * `\u{`_n_`}`, where _n_ is the uppercase hexadecimal representation of the
 * codepoint.
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
rb_u_string_inspect(VALUE self)
{
        const UString *string = RVAL2USTRING(self);

        VALUE result = rb_str_buf_new(0);
        rb_str_buf_cat2(result, "\"");
        const char *p = USTRING_STR(string);
        const char *end = USTRING_END(string);
        while (p < end) {
                unichar c = u_aref_char(p);
                switch (c) {
                case UTF_BAD_INPUT_UNICHAR:
                        p = rb_u_string_inspect_bad_input(p, end, result);
                        continue;
                case '"':
                case '\\':
                        rb_u_string_inspect_special_char(c, result);
                        break;
                case '#':
                        p = rb_u_string_inspect_hash_char(p, end, result);
                        continue;
                case '\n':
                        rb_str_buf_cat2(result, "\\n");
                        break;
                case '\r':
                        rb_str_buf_cat2(result, "\\r");
                        break;
                case '\t':
                        rb_str_buf_cat2(result, "\\t");
                        break;
                case '\f':
                        rb_str_buf_cat2(result, "\\f");
                        break;
                case '\013':
                        rb_str_buf_cat2(result, "\\v");
                        break;
                case '\010':
                        rb_str_buf_cat2(result, "\\b");
                        break;
                case '\007':
                        rb_str_buf_cat2(result, "\\a");
                        break;
                case '\033':
                        rb_str_buf_cat2(result, "\\e");
                        break;
                default:
                        rb_u_string_inspect_default(c, result);
                        break;
                }
                p = u_next(p);
        }

        rb_str_buf_cat2(result, "\".u");

        OBJ_INFECT(result, self);

        return result;
}
