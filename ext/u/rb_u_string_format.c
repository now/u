#include "rb_private.h"
#include <limits.h>

enum DirectiveFlags {
        DIRECTIVE_FLAGS_NONE = 0,
        DIRECTIVE_FLAG_SPACE = 1,
        DIRECTIVE_FLAGS_SHARP = 2,
        DIRECTIVE_FLAGS_PLUS = 4,
        DIRECTIVE_FLAGS_MINUS = 8,
        DIRECTIVE_FLAGS_ZERO = 16,
};

static int
directive_parse_int(const char **p, const char *end, const char *type)
{
        const char *q = p;

        int n = 0;

        while (q < end) {
                unichar c = _rb_u_aref_char_validated(q, end);

                if (!unichar_isdigit(c)) {
                        *p = q;
                        return n;
                }

                q = u_next(q);

                int m = 10 * n + unichar_digit_value(c);
                if (m / 10 != n) {
                        while (q < end && unichar_isdigit(u_aref_char_validated_n(q, end - q)))
                                q = u_next(q);
                        /* TODO: Test this. */
                        rb_raise(rb_eArgError,
                                 "%s too large: %*s > %d",
                                 type, q - p, p, INT_MAX);
                }

                n = m;
        }

        rb_raise(rb_eArgError, "directive missing after %s", type);
}

static bool
directive_argument_number(const char **p, const char *end, const char *type,
                          int *argument_number)
{
        if (*argument_number != 0)
                rb_raise(rb_eArgError,
                         "%s already given", type);

        int n = directive_parse_int(p, end, type);
        if (**p != '$')
                return false;
        *p = u_next(*p);
        *argument_number = n;

        return true;
}

static void
directive_argument_name(const char **p, const char *end, char right,
                        char **argument_name)
{
        if (*argument_name != NULL)
                rb_raise(rb_eArgError,
                         "argument name already given");

        const char *q = p;

        while (q < end && *q != right)
                q = rb_u_next_validated(q, end);

        if (q == end)
                rb_raise(rb_eArgError,
                         "missing argument name end delimiter ‘%c’: %s",
                         right, p);

        const char *base = u_next(*p);
        long length = q - base;
        *argument_name = ALLOC_N(char, length + 1);
        memcpy(*argument_name, base, length);
        *argument_name[length] = '\0';

        *p = rb_u_next_validated(q, end);
}

static int
directive_flags(const char **p, const char *end,
                int *argument_number,
                char **argument_name, bool *argument_name_to_s)
{
        *argument_number = 0;
        *argument_name = NULL;

        int flags = DIRECTIVE_FLAGS_NONE;

        while (*p < end) {
                unichar c = _rb_u_aref_char_validated(*p, end);
                
                int flag;

                switch (c) {
                case ' ':
                        flag = DIRECTIVE_FLAGS_SPACE;
                        break;
                case '#':
                        flag = DIRECTIVE_FLAGS_SHARP;
                        break;
                case '+':
                        flag = DIRECTIVE_FLAGS_PLUS;
                        break;
                case '-':
                        flag = DIRECTIVE_FLAGS_MINUS;
                        break;
                case '0':
                        flag = DIRECTIVE_FLAGS_ZERO;
                        break;
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                        if (argument_name != NULL)
                                rb_raise(rb_eArgError,
                                         "cannot use absolute argument number: argument name already given");
                        if (!directive_argument_number(p, end, "absolute argument number", argument_number))
                                return flags;
                        continue;
                case '<':
                        if (argument_number != 0)
                                rb_raise(rb_eArgError,
                                         "cannot use argument name: absolute argument number already given");
                        directive_argument_name(p, end, '>', argument_name);
                        *argument_name_to_s = false;
                        continue;
                case '{':
                        if (argument_number != 0)
                                rb_raise(rb_eArgError,
                                         "cannot use argument name: absolute argument number already given");
                        directive_argument_name(p, end, '}', argument_name);
                        *argument_name_to_s = true;
                        return flags;
                default:
                        return flags;
                }

                if ((flags & flag) && RTEST(ruby_verbose)) \
                        rb_warn("repeated flag in format: ‘%c’", c);
                flags |= flag;

                *p = u_next(*p);
        }

        if (*p == end)
                rb_raise(rb_eArgError, "directive missing after flags");

        return flags;
}

/* ARGUMENT_NUMBER is set to -1 if the next argument should be use as the
 * width, 0 if the calculated width should be used, or a positive integer if
 * that absolute argument number should be used. Returns 0 if no width was
 * specified (unless ARGUMENT_NUMBER says otherwise). */
static int
directive_width(const char **p, const char *end, int *argument_number)
{
        *argument_number = 0;

        unichar c = _rb_u_aref_char_validated(*p, end);

        if (c != '*')
                return directive_parse_int(p, end, "field width");

        *p = u_next(*p);

        if (!directive_argument_number(p, end,
                                       "absolute field width argument number",
                                       argument_number))
                *argument_number = -1;

        return 0;
}

static int
directive_precision(const char **p, const char *end)
{
        unichar c = _rb_u_aref_char_validated(*p, end);

        if (c != '.')
                return 0;

        *p = u_next(*p);

        return directive_parse_int(p, end, "field precision");
}

static long
directive(const char **p, const char *end, char *result)
{
        int argument_number;
        char *argument_name;
        bool argument_name_to_s;
        int flags = directive_flags(p, end, &argument_number,
                                    &argument_name, &argument_name_to_s);
        if (argument_name_to_s)
                /* TODO: format with %s, skipping rest of stuff below */;

        int width_argument_number;
        int width = directive_width(p, end, &width_argument_number);

        int precision = directive_precision(p, end);

        unichar c = _rb_u_aref_char_validated(*p, end);
}

static long
rb_u_string_format_main(const char *p, const char *end, char *result)
{
        long length = 0;

        while (p < end) {
                if (result != NULL)
                        while (p < end && *p != '%')
                                result[length++] = p;
                else
                        while (p < end && *p != '%')
                                length++;

                if (p == end)
                        break;
                p++;

                length += directive(&p, end, OFFSET_IF(result, length));
        }
}

VALUE
rb_u_string_format(int argc, const VALUE *argv, VALUE self)
{
        const UString *string = RVAL2USTRING(self);
        const char *p = USTRING_STR(string);
        const char *end = USTRING_END(string);

        long length = rb_u_string_format_main(p, end, NULL);
        char *result = ALLOC_N(char, length + 1);
        rb_u_string_format_main(p, end, result);
        result[length] = '\0';

        return rb_u_string_new_own(result, length);
}
