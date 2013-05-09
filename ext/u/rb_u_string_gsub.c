#include "rb_includes.h"
#include "rb_u_re.h"

/* @overload gsub(pattern, replacement)
 *
 *   Returns the receiver with all matches of PATTERN replaced by REPLACEMENT,
 *   inheriting any taint and untrust from the receiver and from REPLACEMENT.
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
 *   @return [U::String]
 *
 * @overload gsub(pattern, replacements)
 *
 *   Returns the receiver with all matches of PATTERN replaced by
 *   REPLACEMENTS#[_match_], where _match_ is the matched substring, inheriting
 *   any taint and untrust from the receiver and from the
 *   REPLACEMENTS#[_match_]es, as well as any taint on REPLACEMENTS.
 *
 *   The Regexp special variables `$&`, `$'`, <code>$\`</code>, `$1`, `$2`, …,
 *   `$`_n_ are updated accordingly.
 *
 *   @param [Regexp, #to_str] pattern
 *   @param [#to_hash] replacements
 *   @raise [RuntimeError] If any replacement is the result being constructed
 *   @raise [Exception] Any error raised by REPLACEMENTS#default, if it gets
 *     called
 *   @return [U::String]
 *
 * @overload gsub(pattern){ |match| … }
 *
 *   Returns the receiver with all matches of PATTERN replaced by the results
 *   of the given block, inheriting any taint and untrust from the receiver and
 *   from the results of the given block.
 *
 *   The Regexp special variables `$&`, `$'`, <code>$\`</code>, `$1`, `$2`, …,
 *   `$`_n_ are updated accordingly.
 *
 *   @param [Regexp, #to_str] pattern
 *   @yieldparam [U::String] match
 *   @yieldreturn [#to_str]
 *   @return [U::String]
 *
 * @overload gsub(pattern)
 *
 *   Returns an Enumerator over the matches of PATTERN in the receiver.
 *
 *   The Regexp special variables `$&`, `$'`, <code>$\`</code>, `$1`, `$2`, …,
 *   `$`_n_ will be updated accordingly.
 *
 *   @param [Regexp, #to_str] pattern
 *   @return [Enumerator] */
VALUE
rb_u_string_gsub(int argc, VALUE *argv, VALUE self)
{
        VALUE pattern, replacement;
        VALUE replacements = Qnil;
        bool use_block = false;
        bool tainted = false;

        if (argc == 1) {
                RETURN_ENUMERATOR(self, argc, argv);
                use_block = true;
        }

        if (rb_scan_args(argc, argv, "11", &pattern, &replacement) == 2) {
                replacements = rb_check_convert_type(replacement, T_HASH,
                                                     "Hash", "to_hash");
                if (NIL_P(replacements))
                        StringValue(replacement);
                if (OBJ_TAINTED(replacement))
                        tainted = true;
        }

        pattern = rb_u_pattern_argument(pattern, true);

        VALUE str = rb_str_to_str(self);
        long begin = rb_reg_search(pattern, str, 0, 0);
        if (begin < 0)
                return self;

        const char *base = RSTRING_PTR(str);
        const char *p = base;
        const char *end = RSTRING_END(str);
        VALUE substituted = rb_u_str_buf_new(RSTRING_LEN(str) + 30);
        do {
                VALUE match = rb_backref_get();
                struct re_registers *registers = RMATCH_REGS(match);
                VALUE result;

                if (use_block || !NIL_P(replacements)) {
                        if (use_block) {
                                VALUE ustr = rb_u_string_new_rb(rb_reg_nth_match(0, match));
                                result = rb_u_string_object_as_string(rb_yield(ustr));
                        } else {
                                VALUE ustr = rb_u_string_new_c(self,
                                                               base + registers->beg[0],
                                                               registers->end[0] - registers->beg[0]);
                                result = rb_u_string_object_as_string(rb_hash_aref(replacements, ustr));
                        }

                        if (result == substituted)
                                rb_u_raise(rb_eRuntimeError,
                                           "result of block is string being built; please try not to cheat");
                } else
                        result =
#ifdef HAVE_RB_REG_REGSUB4
                        rb_reg_regsub(replacement, str, registers, pattern);
#else
                        rb_reg_regsub(replacement, str, registers);
#endif

                if (OBJ_TAINTED(result))
                        tainted = true;

                const struct rb_u_string *value = RVAL2USTRING_ANY(result);

                rb_str_buf_cat(substituted, p, registers->beg[0] - (p - base));
                rb_str_buf_cat(substituted, USTRING_STR(value), USTRING_LENGTH(value));
                OBJ_INFECT(substituted, result);

                p = base + registers->end[0];
                if (registers->beg[0] == registers->end[0])
                        p = u_next(p);
                if (p >= end)
                        break;

                begin = rb_reg_search(pattern, str, registers->end[0], 0);
        } while (begin >= 0);

        if (p < end)
                rb_str_buf_cat(substituted, p, end - p);

        rb_reg_search(pattern, str, end - p, 0);

        RBASIC(substituted)->klass = rb_obj_class(str);
        OBJ_INFECT(substituted, str);
        if (tainted)
                OBJ_TAINT(substituted);

        return rb_u_string_new_rb(substituted);
}
