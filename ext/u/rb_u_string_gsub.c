#include "rb_includes.h"
#include "rb_u_re.h"

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
        VALUE substituted = rb_str_buf_new(RSTRING_LEN(str) + 30);
        do {
                VALUE match = rb_backref_get();
                struct re_registers *registers = RMATCH_REGS(match);
                VALUE result;

                if (use_block || !NIL_P(replacements)) {
                        if (use_block) {
                                VALUE ustr = rb_u_string_new_rb(rb_reg_nth_match(0, match));
                                result = rb_u_string_object_as_string(rb_yield(ustr));
                        } else {
                                VALUE ustr = rb_u_string_new(base + registers->beg[0],
                                                             registers->end[0] - registers->beg[0]);
                                OBJ_INFECT(ustr, self);
                                result = rb_u_string_object_as_string(rb_hash_aref(replacements, ustr));
                        }
                        
                        if (result == substituted)
                                rb_raise(rb_eRuntimeError,
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

                const UString *value = RVAL2USTRING_ANY(result);

                rb_str_buf_cat(substituted, p, registers->beg[0] - (p - base));
                rb_str_buf_cat(substituted, USTRING_STR(value), USTRING_LENGTH(value));

                p = base + registers->end[0];
                if (registers->beg[0] == registers->end[0]) {
                        p = u_find_next(p, end);
                        if (p == NULL)
                                break;
                }
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
