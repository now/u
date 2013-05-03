#include "rb_includes.h"

#define SYMBOL2MODE(symbol, mode, id) do {              \
        static ID id_##symbol;                          \
        if (id_##symbol == 0)                           \
                id_##symbol = rb_intern(#symbol);       \
        if (id == id_##symbol)                          \
                return mode;                            \
} while (0)

static enum u_normalize_mode
symbol_to_mode(VALUE symbol)
{
        if (!SYMBOL_P(symbol)) {
                VALUE inspected = rb_inspect(symbol);

                rb_u_raise(rb_eTypeError,
                           "not a symbol: %s",
                           StringValuePtr(inspected));
        }

        ID id = SYM2ID(symbol);

        SYMBOL2MODE(default, U_NORMALIZE_DEFAULT, id);
        SYMBOL2MODE(nfd, U_NORMALIZE_NFD, id);
        SYMBOL2MODE(default_compose, U_NORMALIZE_DEFAULT_COMPOSE, id);
        SYMBOL2MODE(nfc, U_NORMALIZE_NFC, id);
        SYMBOL2MODE(all, U_NORMALIZE_ALL, id);
        SYMBOL2MODE(nfkd, U_NORMALIZE_NFKD, id);
        SYMBOL2MODE(all_compose, U_NORMALIZE_ALL_COMPOSE, id);
        SYMBOL2MODE(nfkc, U_NORMALIZE_NFKC, id);

        rb_u_raise(rb_eArgError,
                   "unknown normalization mode: :%s",
                   rb_id2name(SYM2ID(symbol)));
}

/* @overload normalize(mode = :default)
 *
 *   Returns the normalization of the receiver according to MODE, inheriting
 *   any taint and untrust.
 *
 *   Normalization is the process of converting characters and sequences of
 *   characters in string into a canonical form.  This process includes dealing
 *   with whether characters are represented by a composed character or a base
 *   character and combining marks, such as accents.
 *
 *   The possible normalization modes are
 *
 *   <table>
 *     <thead>
 *       <tr><th>Modes</th><th>Description</th></tr>
 *     </thead>
 *     <tbody>
 *       <tr>
 *         <td><code>:default</code>, <code>:nfd</code></td>
 *         <td>Normalizes characters to their maximally decomposed form,
 *         ordering accents and so on according to their combining class</td>
 *       </tr>
 *       <tr>
 *         <td><code>:default_compose</code>, <code>:nfc</code></td>
 *         <td>Normalizes according to <code>:default</code>, then composes any
 *         decomposed characters</td>
 *       </tr>
 *       <tr>
 *         <td><code>:all</code>, <code>:nfkd</code></td>
 *         <td>Normalizes according to <code>:default</code> and also
 *         normalizes “compatibility” characters, such as replacing U+00B3
 *         SUPERSCRIPT THREE with U+0033 DIGIT THREE</td>
 *       </tr>
 *       <tr>
 *         <td><code>:all_compose</code>, <code>:nfkc</code></td>
 *         <td>Normalizes according to <code>:all</code>, then composes any
 *         decomposed characters</td>
 *       </tr>
 *     </tbody>
 *   </table>
 *
 *   @param [#to_sym] mode
 *   @return [U::String] */
VALUE
rb_u_string_normalize(int argc, VALUE *argv, VALUE self)
{
        const struct rb_u_string *string = RVAL2USTRING(self);

        VALUE rbmode;
        enum u_normalize_mode mode = U_NORMALIZE_DEFAULT;
        if (rb_scan_args(argc, argv, "01", &rbmode) == 1)
                mode = symbol_to_mode(rbmode);

        size_t n = u_normalize(NULL, 0,
                               USTRING_STR(string), USTRING_LENGTH(string),
                               mode);
        char *normalized = ALLOC_N(char, n + 1);
        n = u_normalize(normalized, n + 1,
                        USTRING_STR(string), USTRING_LENGTH(string),
                        mode);
        char *t = REALLOC_N(normalized, char, n + 1);
        if (t != NULL)
                normalized = t;

        return rb_u_string_new_c_own(self, normalized, n);
}
