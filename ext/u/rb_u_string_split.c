#include "rb_includes.h"
#include "rb_u_re.h"

static VALUE
rb_u_string_split_trim(VALUE result, bool limit_given, int limit)
{
        if (limit_given || limit != 0)
                return result;

        long length;
        while ((length = RARRAY_LEN(result)) > 0 &&
               USTRING_LENGTH(RVAL2USTRING(RARRAY_PTR(result)[length - 1])) == 0)
                rb_ary_pop(result);

        return result;
}

static VALUE
rb_u_string_split_rest(VALUE self, long offset, bool limit_given, int limit, VALUE result)
{
        const UString *string = RVAL2USTRING(self);
        long length = USTRING_LENGTH(string);

        if (length > 0 && (limit_given || length > offset || limit < 0))
                rb_ary_push(result,
                            length == offset ?
                                rb_u_string_new_empty(self) :
                                rb_u_string_new_subsequence(self,
                                                            offset,
                                                            length - offset));

        return rb_u_string_split_trim(result, limit_given, limit);
}

static VALUE
rb_u_string_split_awk(VALUE self, bool limit_given, int limit)
{
        VALUE result = rb_ary_new();

        const UString *string = RVAL2USTRING(self);
        const char *begin = USTRING_STR(string);
        const char *p = begin;
        const char *end = USTRING_END(string);
        int i = 1;
        while (p < end) {
                while (p < end && unichar_isspace(_rb_u_aref_char_validated(p, end)))
                        p = u_next(p);

                if (p == end || (limit_given && i >= limit))
                        break;
                i++;

                const char *q = p;
                while (q < end && !unichar_isspace(_rb_u_aref_char_validated(q, end)))
                        q = u_next(q);

                rb_ary_push(result,
                            rb_u_string_new_subsequence(self,
                                                        p - begin,
                                                        q - p));
                p = q;
        }

        return rb_u_string_split_rest(self, p - begin, limit_given, limit, result);
}

static VALUE
rb_u_string_split_string(VALUE self, VALUE rbseparator, bool limit_given, int limit)
{
        const UString *string = RVAL2USTRING(self);
        const UString *separator = RVAL2USTRING_ANY(rbseparator);

        const char *begin = USTRING_STR(string);
        const char *p = begin;
        const char *end = USTRING_END(string);

        const char *s_p = USTRING_STR(separator);
        long s_len = USTRING_LENGTH(separator);

        rb_u_validate(p, USTRING_LENGTH(string));
        rb_u_validate(s_p, s_len);

        VALUE result = rb_ary_new();

        /* TODO: Better variable name. */
        long offset;
        for (int i = 1; (!limit_given || i < limit) && p < end; i++) {
                if ((offset = rb_u_memsearch(s_p, s_len, p, end - p)) < 0)
                        break;
                rb_ary_push(result, rb_u_string_new_subsequence(self, p - begin, offset));
                p += offset + s_len;
        }

        return rb_u_string_split_rest(self, p - begin, limit_given, limit, result);
}

static void
rb_u_string_split_pattern_push_registers(VALUE self,
                                         struct re_registers *registers,
                                         VALUE result)
{
        for (int i = 1; i < registers->num_regs; i++) {
                if (registers->beg[i] == -1)
                        continue;
                rb_ary_push(result,
                            registers->beg[i] == registers->end[i] ?
                                rb_u_string_new_empty(self) :
                                rb_u_string_new_subsequence(self,
                                                            registers->beg[i],
                                                            registers->end[i] - registers->beg[i]));
        }
}

static VALUE
rb_u_string_split_pattern(VALUE self, VALUE pattern, bool limit_given, int limit)
{
        VALUE str = rb_str_to_str(self);

        const char *begin = RSTRING_PTR(str);
        const char *p = begin;
        const char *end = RSTRING_END(str);

        VALUE result = rb_ary_new();

        bool last_was_empty = false;

        long start = 0;
        /* TODO: Better variable name. */
        long offset;
        int i = 1;
        while ((offset = rb_reg_search(pattern, str, start, 0)) >= 0) {
                struct re_registers *registers = RMATCH_REGS(rb_backref_get());
                if (start == offset && registers->beg[0] == registers->end[0]) {
                        if (begin == NULL) {
                                rb_ary_push(result, rb_u_string_new_empty(self));
                                break;
                        } else if (last_was_empty) {
                                rb_ary_push(result,
                                            rb_u_string_new_subsequence(self,
                                                                        p - begin,
                                                                        rb_u_next_validated(p, end) - p));
                        } else {
                                if (begin + start == end)
                                        start++;
                                else
                                        start += rb_u_next_validated(p, end) - p;
                                last_was_empty = true;
                                continue;
                        }
                } else {
                        rb_ary_push(result,
                                    rb_u_string_new_subsequence(self,
                                                                p - begin,
                                                                offset - (p - begin)));
                        start = registers->end[0];
                }
                last_was_empty = false;
                p = begin + start;

                rb_u_string_split_pattern_push_registers(self, registers, result);

                i++;
                if (limit_given && i == limit)
                        break;
        }

        return rb_u_string_split_rest(self, p - begin, limit_given, limit, result);
}

/* @overload split(pattern = $;, limit = 0)
 *
 *   Returns the receiver split into LIMIT substrings separated by PATTERN,
 *   each inheriting any taint and untrust.
 *
 *   If PATTERN = `$;` = nil or PATTERN = `' '`, splits according to AWK rules,
 *   that is, any {#space?} prefix is skipped, then substrings are separated by
 *   non-empty {#space?} substrings.
 *
 *   If LIMIT < 0, then no limit is imposed and trailing {#empty?} substrings
 *   aren’t removed.
 *
 *   If LIMIT = 0, then no limit is imposed and trailing {#empty?} substrings
 *   are removed.
 *
 *   If LIMIT = 1, then, if {#length} = 0, the result will be empty, otherwise
 *   it will consist of the receiver only.
 *
 *   If LIMIT > 1, then the receiver is split into at most LIMIT substrings.
 *
 *   @param [Regexp, #to_str] pattern
 *   @param [#to_int] limit
 *   @return [Array<U::String>] */
VALUE
rb_u_string_split_m(int argc, VALUE *argv, VALUE self)
{
        VALUE rbpattern, rblimit;
        int limit = 0;
        bool limit_given;

        if (rb_scan_args(argc, argv, "02", &rbpattern, &rblimit) == 2)
                limit = NUM2INT(rblimit);

        const UString *string = RVAL2USTRING(self);

        if (limit == 1) {
                if (USTRING_LENGTH(string) == 0)
                        return rb_ary_new2(0);

                return rb_ary_new3(1, self);
        }

        limit_given = !NIL_P(rblimit) && limit >= 0;

        if (NIL_P(rbpattern) && NIL_P(rb_fs))
                return rb_u_string_split_awk(self, limit_given, limit);
        else if (NIL_P(rbpattern))
                rbpattern = rb_fs;

        if (TYPE(rbpattern) != T_STRING && !RTEST(rb_obj_is_kind_of(rbpattern, rb_cUString)))
                return rb_u_string_split_pattern(self,
                                                 rb_u_pattern_argument(rbpattern, true),
                                                 limit_given,
                                                 limit);

        const UString *pattern = RVAL2USTRING_ANY(rbpattern);
        const char *p = USTRING_STR(pattern);
        long length = USTRING_LENGTH(pattern);

        if (length == 0)
                return rb_u_string_split_pattern(self,
                                                 rb_reg_regcomp(rb_str_to_str(rbpattern)),
                                                 limit_given,
                                                 limit);
        else if (length == 1 && *p == ' ')
                return rb_u_string_split_awk(self, limit_given, limit);
        else
                return rb_u_string_split_string(self, rbpattern, limit_given, limit);
}
