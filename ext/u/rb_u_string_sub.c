#include "rb_includes.h"
#include "rb_u_re.h"

/* @overload sub(pattern, replacement)
 *
 *   Returns the receiver with the first match of PATTERN replaced by
 *   REPLACEMENT, inheriting any taint and untrust from the receiver and from
 *   REPLACEMENT, or nil if there’s no match.
 *
 *   The REPLACEMENT is used as a specification for what to replace matches
 *   with:
 *
 *   <table>
 *     <thead>
 *       <tr><th>Specification</th><th>Replacement</th></tr>
 *     </thead>
 *     <tbody>
 *       <tr>
 *         <td><code>\1</code>, <code>\2</code>, …, <code>\</code><em>n</em></td>
 *         <td>Numbered sub-match <em>n</em></td>
 *       </tr>
 *       <tr>
 *         <td><code>\k&lt;</code><em>name</em><code>></code></td>
 *         <td>Named sub-match <em>name</em></td>
 *       </tr>
 *     </tbody>
 *   </table>
 *
 *   The Regexp special variables `$&`, `$'`, <code>$\`</code>, `$1`, `$2`, …,
 *   `$`_n_ are updated accordingly.
 *
 *   @param [Regexp, #to_str] pattern
 *   @param [#to_str] replacement
 *   @return [U::String, nil]
 *
 * @overload sub(pattern, replacements)
 *
 *   Returns the receiver with the first match of PATTERN replaced by
 *   REPLACEMENTS#[_match_], where _match_ is the matched substring, inheriting
 *   any taint and untrust from the receiver, REPLACEMENTS, and
 *   REPLACEMENTS#[_match_], or nil if there’s no match.
 *
 *   The Regexp special variables `$&`, `$'`, <code>$\`</code>, `$1`, `$2`, …,
 *   `$`_n_ are updated accordingly.
 *
 *   @param [Regexp, #to_str] pattern
 *   @param [#to_hash] replacements
 *   @raise [Exception] Any error raised by REPLACEMENTS#default, if it gets
 *     called
 *   @return [U::String, nil]
 *
 * @overload sub(pattern){ |match| … }
 *
 *   Returns the receiver with all instances of PATTERN replaced by the results
 *   of the given block, inheriting any taint and untrust from the receiver and
 *   from the results of the given block, or nil if there’s no match.
 *
 *   The Regexp special variables `$&`, `$'`, <code>$\`</code>, `$1`, `$2`, …,
 *   `$`_n_ are updated accordingly.
 *
 *   @param [Regexp, #to_str] pattern
 *   @yieldparam [U::String] match
 *   @yieldreturn [#to_str]
 *   @return [U::String, nil] */
VALUE
rb_u_string_sub(int argc, VALUE *argv, VALUE self)
{
        VALUE pattern, replacement;
        VALUE replacements = Qnil;
        bool use_block = false;
        bool tainted = false;
        bool untrusted = false;

        if (argc == 1)
                use_block = true;

        if (rb_scan_args(argc, argv, "11", &pattern, &replacement) == 2) {
                replacements = rb_check_convert_type(replacement, T_HASH,
                                                     "Hash", "to_hash");
                if (NIL_P(replacements))
                        StringValue(replacement);
                if (OBJ_TAINTED(replacement))
                        tainted = true;
                if (OBJ_UNTRUSTED(replacement))
                        untrusted = true;
        }

        pattern = rb_u_pattern_argument(pattern, true);

        VALUE str = rb_str_to_str(self);
        long begin = rb_reg_search(pattern, str, 0, 0);
        if (begin < 0)
                return Qnil;

        VALUE match = rb_backref_get();
        struct re_registers *registers = RMATCH_REGS(match);
        VALUE result;
        /* TODO: Refactor this. */
        if (use_block || !NIL_P(replacements)) {
                if (use_block) {
                        VALUE ustr = rb_u_string_new_rb(rb_reg_nth_match(0, match));
                        result = rb_u_string_object_as_string(rb_yield(ustr));
                } else {
                        VALUE ustr = rb_u_string_new_c(self,
                                                       RSTRING_PTR(str) + registers->beg[0],
                                                       registers->end[0] - registers->beg[0]);
                        result = rb_u_string_object_as_string(rb_hash_aref(replacements, ustr));
                }
        } else
                result =
#ifdef HAVE_RB_REG_REGSUB4
                        rb_reg_regsub(replacement, str, registers, pattern);
#else
                        rb_reg_regsub(replacement, str, registers);
#endif

        if (OBJ_TAINTED(result))
                tainted = true;
        if (OBJ_UNTRUSTED(result))
                untrusted = true;

        const struct rb_u_string *value = RVAL2USTRING_ANY(result);

        size_t length = registers->beg[0] +
                USTRING_LENGTH(value) +
                (RSTRING_LEN(str) - registers->end[0]);
        char *base = ALLOC_N(char, length + 1);
        MEMCPY(base,
               RSTRING_PTR(str),
               char,
               registers->beg[0]);
        MEMCPY(base + registers->beg[0],
               USTRING_STR(value),
               char,
               USTRING_LENGTH(value));
        MEMCPY(base + registers->beg[0] + USTRING_LENGTH(value),
               RSTRING_PTR(str) + registers->end[0],
               char,
               RSTRING_LEN(str) - registers->end[0]);
        base[length] = '\0';

        VALUE substituted = rb_u_string_new_c_own(self, base, length);
        if (tainted)
                OBJ_TAINT(substituted);
        if (untrusted)
                OBJ_UNTRUST(substituted);
        return substituted;
}
