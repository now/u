#include "rb_includes.h"

static void
rb_u_string_inspect_bad_input(const char *p, const char *q, VALUE result)
{
        while (p < q) {
                char hex[5];
                snprintf(hex, lengthof(hex), "\\x%02X", *p & 0xff);
                rb_str_buf_cat2(result, hex);
                p++;
        }
}

static void
rb_u_string_inspect_special_char(uint32_t c, VALUE result)
{
        char str[U_CHAR_MAX_BYTE_LENGTH];

        rb_str_buf_cat2(result, "\\");
        rb_str_buf_cat(result, str, u_char_to_u(c, str));
}

static void
rb_u_string_inspect_escaped_char(uint32_t c, VALUE result)
{
        char str[4 + 8 + 1];

        if (c < 0x10000)
                snprintf(str, lengthof(str), "\\u%04X", c);
        else
                snprintf(str, lengthof(str), "\\u{%X}", c & 0xffffffff);

        rb_str_buf_cat2(result, str);
}

static void
rb_u_string_inspect_default(uint32_t c, VALUE result)
{
        if (!u_char_isprint(c)) {
                rb_u_string_inspect_escaped_char(c, result);
                return;
        }

        char str[U_CHAR_MAX_BYTE_LENGTH];
        rb_str_buf_cat(result, str, u_char_to_u(c, str));
}

#define REPLACEMENT_CHARACTER ((uint32_t)0xfffd)

static const char *
rb_u_string_inspect_hash_char(const char *q, const char *end,
                              VALUE result)
{
        if (q == end) {
                rb_str_buf_cat2(result, "#");
                return q;
        }

        const char *p = q;
        uint32_t c = u_decode(&q, p, end);
        switch (c) {
        case REPLACEMENT_CHARACTER:
                rb_str_buf_cat2(result, "#");
                if (!u_valid(p, q - p, NULL))
                        rb_u_string_inspect_bad_input(p, q, result);
                else
                        rb_u_string_inspect_default(c, result);
                return q;
        case '$':
        case '@':
        case '{':
                rb_str_buf_cat2(result, "\\#");
                rb_u_string_inspect_default(c, result);
                return q;
        default:
                rb_str_buf_cat2(result, "#");
                return p;
        }
}

/* Returns the receiver in a reader-friendly inspectable format, inheriting
 * any taint and untrust, encoded using UTF-8.
 *
 * The reader-friendly inspectable format looks like “`"…".u`”.  Inside the
 * “…”, any {#print?} characters are output as-is, the following special
 * characters are escaped according to the following table:
 *
 * <table>
 *   <thead><tr><th>Character</th><th>Dumped Sequence</th></tr></thead>
 *   <tbody>
 *     <tr><td>U+0022 QUOTATION MARK</td><td><code>\"</code></td></tr>
 *     <tr><td>U+005C REVERSE SOLIDUS</td><td><code>\\</code></td></tr>
 *     <tr><td>U+000A LINE FEED (LF)</td><td><code>\n</code></td></tr>
 *     <tr><td>U+000D CARRIAGE RETURN (CR)</td><td><code>\r</code></td></tr>
 *     <tr><td>U+0009 CHARACTER TABULATION</td><td><code>\t</code></td></tr>
 *     <tr><td>U+000C FORM FEED (FF)</td><td><code>\f</code></td></tr>
 *     <tr><td>U+000B LINE TABULATION</td><td><code>\v</code></td></tr>
 *     <tr><td>U+0008 BACKSPACE</td><td><code>\b</code></td></tr>
 *     <tr><td>U+0007 BELL</td><td><code>\a</code></td></tr>
 *     <tr><td>U+001B ESCAPE</td><td><code>\e</code></td></tr>
 *   </tbody>
 * </table>
 *
 * the following special sequences are also escaped:
 *
 * <table>
 *   <thead><tr><th>Character</th><th>Dumped Sequence</th></tr></thead>
 *   <tbody>
 *     <tr><td><code>#$</code></td><td><code>\#$</code></td></tr>
 *     <tr><td><code>#@</code></td><td><code>\#@</code></td></tr>
 *     <tr><td><code>#{</code></td><td><code>\#{</code></td></tr>
 *   </tbody>
 * </table>
 *
 * Valid UTF-8 byte sequences representing code points < 0x10000 are output as
 * `\u`_n_, where _n_ is the four-digit uppercase hexadecimal representation
 * of the code point.
 *
 * Valid UTF-8 byte sequences representing code points ≥ 0x10000 are output as
 * `\u{`_n_`}`, where _n_ is the uppercase hexadecimal representation of the
 * code point.
 *
 * Any other byte is output as `\x`_n_, where _n_ is the two-digit uppercase
 * hexadecimal representation of the byte’s value.
 *
 * @return [String] */
VALUE
rb_u_string_inspect(VALUE self)
{
        const struct rb_u_string *string = RVAL2USTRING(self);

        VALUE result = rb_u_str_buf_new(0);
        rb_str_buf_cat2(result, "\"");
        const char *p = USTRING_STR(string);
        const char *end = USTRING_END(string);
        while (p < end) {
                const char *q;
                uint32_t c = u_decode(&q, p, end);
                switch (c) {
                case '"':
                case '\\':
                        rb_u_string_inspect_special_char(c, result);
                        break;
                case '#':
                        p = rb_u_string_inspect_hash_char(q, end, result);
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
                case REPLACEMENT_CHARACTER:
                        if (!u_valid(p, q - p, NULL)) {
                                rb_u_string_inspect_bad_input(p, q, result);
                                break;
                        }
                        /* fall through */
                default:
                        rb_u_string_inspect_default(c, result);
                        break;
                }
                p = q;
        }

        rb_str_buf_cat2(result, "\".u");

        OBJ_INFECT(result, self);

        return result;
}
