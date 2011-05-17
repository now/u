#include "rb_includes.h"
#include <limits.h>
#include <intern.h>
#include "rb_u_buffer.h"
#include "rb_u_string_internal_bignum.h"

enum DirectiveFlags {
        DIRECTIVE_FLAGS_NONE = 0,
        DIRECTIVE_FLAGS_SPACE = 1,
        DIRECTIVE_FLAGS_SHARP = 2,
        DIRECTIVE_FLAGS_PLUS = 4,
        DIRECTIVE_FLAGS_MINUS = 8,
        DIRECTIVE_FLAGS_ZERO = 16,
        DIRECTIVE_FLAGS_NUMBER =
                DIRECTIVE_FLAGS_SPACE |
                DIRECTIVE_FLAGS_PLUS |
                DIRECTIVE_FLAGS_MINUS |
                DIRECTIVE_FLAGS_ZERO,
        DIRECTIVE_FLAGS_DECIMAL =
                DIRECTIVE_FLAGS_NUMBER |
                DIRECTIVE_FLAGS_SHARP
};

struct format_arguments {
        int argc;
        const VALUE *argv;
        int i;
        bool absolute;
        VALUE names;
};

#ifndef HAVE_RB_HASH_LOOKUP2
#  include <st.h>

static VALUE
rb_hash_lookup2(VALUE hash, VALUE key, VALUE default_value)
{
        VALUE value;

        if (st_lookup(RHASH(hash)->tbl, key, &value))
                return value;

        return default_value;
}
#endif

#ifndef HAVE_RB_EKEYERROR
#  define rb_eKeyError rb_eArgError
#endif

static int
directive_parse_int(const char **p, const char *end, const char *type)
{
        const char *q = *p;

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
                                 type, q - *p, *p, INT_MAX);
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

        const char *q = *p;
        int n = directive_parse_int(&q, end, type);
        if (*q != '$')
                return false;
        *p = u_next(q);
        *argument_number = n;

        return true;
}

static void
directive_argument_name(const char **p, const char *end, char right,
                        ID *argument_id)
{
        if (*argument_id != 0)
                rb_raise(rb_eArgError,
                         "argument name already given");

        const char *q = *p;

        while (q < end && *q != right)
                q = rb_u_next_validated(q, end);

        if (q == end)
                rb_raise(rb_eArgError,
                         "missing argument name end delimiter ‘%c’: %s",
                         right, p);

        const char *base = u_next(*p);
        long length = q - base;
#ifdef HAVE_RB_INTERN3 && HAVE_RB_UTF8_ENCODING
        *argument_id = rb_intern3(base, length, rb_utf8_encoding());
#else
        char name[length + 1];
        memcpy(name, base, length);
        name[length] = '\0';
        *argument_id = rb_intern(name);
#endif

        *p = rb_u_next_validated(q, end);
}

static VALUE
format_arguments_absolute(struct format_arguments *arguments, int absolute)
{
        if (arguments->i > 0)
                rb_raise(rb_eArgError,
                         "cannot use absolute argument number %d: relative argument number already used",
                         absolute);

        if (arguments->names != Qundef)
                rb_raise(rb_eArgError,
                         "cannot use absolute argument number %d: argument name already given",
                         absolute);

        arguments->absolute = true;

        if (absolute - 1 > arguments->argc)
                /* TODO: Check error output. (%d > %d) */
                rb_raise(rb_eArgError,
                         "absolute argument number beyond end of argument list: %d > %d",
                         absolute, arguments->argc + 1);

        return arguments->argv[absolute - 1];
}

static VALUE
format_arguments_id(struct format_arguments *arguments, ID id)
{
        if (arguments->i > 0)
                rb_raise(rb_eArgError,
                         "cannot use named argument “%s”: relative argument number already used",
                         rb_id2name(id));

        if (arguments->absolute)
                rb_raise(rb_eArgError,
                         "cannot use named argument “%s”: absolute argument number already used",
                         rb_id2name(id));

        if (arguments->names == Qundef) {
                VALUE tmp;

                if (arguments->argc != 1 ||
                    NIL_P(tmp = rb_check_convert_type(arguments->argv[0], T_HASH, "Hash", "to_hash")))
                        rb_raise(rb_eArgError,
                                 "one Hash argument required when using named arguments in format");

                arguments->names = tmp;
        }

        VALUE argument = rb_hash_lookup2(arguments->names, ID2SYM(id), Qundef);
        if (argument == Qundef)
                rb_raise(rb_eKeyError, "named argument not found: %s", rb_id2name(id));

        return argument;
}

static VALUE
format_arguments_next(struct format_arguments *arguments)
{
        if (arguments->absolute)
                rb_raise(rb_eArgError,
                         "cannot use positional argument numbers after absolute argument numbers");

        if (arguments->names != Qundef)
                rb_raise(rb_eArgError,
                         "cannot use positional argument numbers after named arguments");

        arguments->i++;

        if (arguments->i > arguments->argc)
                need_at_least_n_arguments(arguments->argc, arguments->i);

        return arguments->argv[arguments->i - 1];
}

static int
directive_flags(const char **p, const char *end,
                struct format_arguments *arguments,
                VALUE *argument, bool *argument_to_s)
{
        int flags = DIRECTIVE_FLAGS_NONE;
        int argument_number = 0;
        ID argument_id = 0;

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
                        if (!directive_argument_number(p, end, "absolute argument number", &argument_number))
                                goto setup_argument;
                        if (argument_id != 0)
                                rb_raise(rb_eArgError,
                                         "cannot use absolute argument number: argument name already given");
                        continue;
                case '<':
                        if (argument_number != 0)
                                rb_raise(rb_eArgError,
                                         "cannot use argument name: absolute argument number already given");
                        directive_argument_name(p, end, '>', &argument_id);
                        *argument_to_s = false;
                        continue;
                case '{':
                        if (argument_number != 0)
                                rb_raise(rb_eArgError,
                                         "cannot use argument name: absolute argument number already given");
                        directive_argument_name(p, end, '}', &argument_id);
                        *argument_to_s = true;
                        goto setup_argument;
                default:
                        goto setup_argument;
                }

                if ((flags & flag) && RTEST(ruby_verbose)) \
                        rb_warn("repeated flag in format: ‘%c’", c);
                flags |= flag;

                *p = u_next(*p);
        }

        if (*p == end)
                rb_raise(rb_eArgError, "directive missing after flags");

setup_argument:
        if (argument_number != 0)
                *argument = format_arguments_absolute(arguments, argument_number);
        else if (argument_id != 0)
                *argument = format_arguments_id(arguments, argument_id);

        return flags;
}

static int
directive_width(const char **p, const char *end,
                struct format_arguments *arguments,
                int *flags)
{
        unichar c = _rb_u_aref_char_validated(*p, end);

        if (c != '*')
                return directive_parse_int(p, end, "field width");

        *p = u_next(*p);

        int argument_number = 0;
        VALUE argument = directive_argument_number(p, end,
                                                   "absolute field width argument number",
                                                   &argument_number) ?
                format_arguments_absolute(arguments, argument_number) :
                format_arguments_next(arguments);
        int width = NUM2INT(argument);
        if (width < 0) {
                *flags |= DIRECTIVE_FLAGS_MINUS;
                width = -width;
        }

        return width;
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

static void
directive_validate_flags(unichar c, int flags, int valid)
{
        char invalid[6];
        int n = 0;

        if ((flags & DIRECTIVE_FLAGS_SPACE) && !(valid & DIRECTIVE_FLAGS_SPACE))
                invalid[n++] = ' ';
        if ((flags & DIRECTIVE_FLAGS_SHARP) && !(valid & DIRECTIVE_FLAGS_SHARP))
                invalid[n++] = '#';
        if ((flags & DIRECTIVE_FLAGS_PLUS) && !(valid & DIRECTIVE_FLAGS_PLUS))
                invalid[n++] = '+';
        if ((flags & DIRECTIVE_FLAGS_MINUS) && !(valid & DIRECTIVE_FLAGS_MINUS))
                invalid[n++] = '-';
        if ((flags & DIRECTIVE_FLAGS_ZERO) && !(valid & DIRECTIVE_FLAGS_ZERO))
                invalid[n++] = '0';
        if (n == 0)
                return;

        invalid[n] = '\0';

        if (n == 1)
                rb_raise(rb_eArgError,
                         "invalid flag ‘%s’ given to directive ‘%lc’",
                         invalid, c);

        rb_raise(rb_eArgError,
                 "invalid flags “%s” given to directive ‘%lc’",
                 invalid, c);
}

static void
directive_validate_argument_not_given(unichar c, VALUE argument)
{
        if (argument != Qundef)
                rb_raise(rb_eArgError,
                         "directive does not take an argument: %lc",
                         c);
}

static void
directive_validate_width_not_given(unichar c, int width)
{
        if (width != 0)
                rb_raise(rb_eArgError,
                         "directive does not allow specifying a width: %lc",
                         c);
}

static void
directive_validate_precision_not_given(unichar c, int precision)
{
        if (precision != 0)
                rb_raise(rb_eArgError,
                         "directive does not allow specifying a precision: %lc",
                         c);
}

static void
directive_escape(unichar c, VALUE result)
{
        rb_u_buffer_append_unichar(result, c);
}

static void
directive_pad(int flags, int padding, const char *str, long length, VALUE result)
{
        if (flags & DIRECTIVE_FLAGS_MINUS) {
                rb_u_buffer_append(result, str, length);
                rb_u_buffer_append_unichar_n(result, ' ', padding);
        } else {
                rb_u_buffer_append_unichar_n(result, ' ', padding);
                rb_u_buffer_append(result, str, length);
        }
}

static void
directive_character(UNUSED(unichar directive), int flags, int width, UNUSED(int precision), VALUE argument, VALUE result)
{
        VALUE tmp = rb_u_string_check_type(argument);

        unichar c;
        const char *p;
        int length;

        if (!NIL_P(tmp)) {
                const UString *string = RVAL2USTRING_ANY(tmp);
                p = USTRING_STR(string);
                c = _rb_u_aref_char_validated(p, USTRING_END(string));
                length = u_next(p) - p;
        } else {
                char buf[MAX_UNICHAR_BYTE_LENGTH];
                p = buf;
                c = NUM2INT(argument);
                length = rb_unichar_to_u(c, buf);
        }

        int padding = width - (unichar_iswide(c) ? 2 : 1);
        if (padding < 0) {
                rb_u_buffer_append_unichar(result, c);
                return;
        }

        directive_pad(flags, padding, p, length, result);
}

static void
directive_string(UNUSED(unichar directive), int flags, int width, int precision, VALUE argument, VALUE result)
{
        VALUE str = rb_u_string_object_as_string(argument);

        if (OBJ_TAINTED(str))
                OBJ_TAINT(result);

        const UString *string = RVAL2USTRING_ANY(str);
        const char *p = USTRING_STR(string);
        long length = USTRING_LENGTH(string);

        if (precision > 0) {
                /* TODO: Should really wrap this in a rb_u_offset_to_pointer_n
                 * so that we can validate that the region walked is valid.
                 */
                const char *q = u_offset_to_pointer_n(p, precision, length);
                if (q != NULL)
                        length = q - p;
        }

        long n_chars;
        if (width == 0 || width < (n_chars = u_length_n(p, length))) {
                rb_u_buffer_append(result, p, length);
                return;
        }

        directive_pad(flags, width - (int)n_chars, p, length, result);
}

static void
directive_inspect(unichar directive, int flags, int width, int precision, VALUE argument, VALUE result)
{
        directive_string(directive, flags, width, precision, rb_inspect(argument), result);
}

static long
directive_integer_value(VALUE argument, VALUE *bignum)
{
        switch (TYPE(argument)) {
        case T_FLOAT: {
                if (FIXABLE(RFLOAT_VALUE(argument)))
                        return (long)RFLOAT_VALUE(argument);
                VALUE result = rb_dbl2big(RFLOAT_VALUE(argument));
                if (FIXNUM_P(result))
                        return FIX2LONG(result);
                *bignum = result;
                return 0;
        }
        case T_STRING:
                return directive_integer_value(rb_str_to_inum(argument, 0, true), bignum);
        case T_BIGNUM:
                *bignum = argument;
                return 0;
        case T_FIXNUM:
                return FIX2LONG(argument);
        default:
                if (rb_obj_is_kind_of(argument, rb_cUString))
                        return directive_integer_value(rb_u_string_to_inum(argument, 0, true), bignum);
                return directive_integer_value(rb_Integer(argument), bignum);
        }
}

static void
directive_number(unichar directive, int flags, int width, int precision, const char *digits, int length, VALUE result)
{
        if ((flags & DIRECTIVE_FLAGS_MINUS) && (flags & DIRECTIVE_FLAGS_ZERO) && RTEST(ruby_verbose))
                rb_warn("‘%lc’ directive ignores ‘0’ flag when ‘-’ flag has been specified",
                        directive);

        if (precision > 0 && (flags & DIRECTIVE_FLAGS_ZERO) && RTEST(ruby_verbose))
                rb_warn("‘%lc’ directive ignores ‘0’ flag when precision (%d) has been specified",
                        directive, precision);

        char sc = '\0';

        if (digits[0] == '-') {
                digits++;
                length--;
                sc = '-';
        } else if (flags & DIRECTIVE_FLAGS_PLUS)
                sc = '+';
        else if (flags & DIRECTIVE_FLAGS_SPACE)
                sc = ' ';

        if (sc != '\0' && width > 0)
                width--;

        if (precision < length) {
                /* TODO: What is this test good for? */
                if (precision == 0 && length == 1 && *digits == '0')
                        length = 0;
                precision = length;
        }
        width -= precision;

        if (width > 0 && !(flags & DIRECTIVE_FLAGS_MINUS) && !(flags & DIRECTIVE_FLAGS_ZERO))
                rb_u_buffer_append_unichar_n(result, ' ', width);

        if (sc != '\0')
                rb_u_buffer_append_unichar(result, sc);

        if (width > 0 && !(flags & DIRECTIVE_FLAGS_MINUS) && (flags & DIRECTIVE_FLAGS_ZERO))
                rb_u_buffer_append_unichar_n(result, '0', width);

        if (precision > length && !(flags & DIRECTIVE_FLAGS_MINUS)) {
                char c = '0';

                rb_u_buffer_append_unichar_n(result, c, precision - length);
        }

        rb_u_buffer_append(result, digits, length);

        if (width > 0 && (flags & DIRECTIVE_FLAGS_MINUS))
                rb_u_buffer_append_unichar_n(result, ' ', width);
}

static void
directive_integer_long(unichar directive, int flags, int width, int precision, long argument, VALUE result)
{
        char fixed[64];
        const char *digits = fixed;
        int length = snprintf(fixed, sizeof(fixed), "%ld", argument);
        if ((unsigned)length >= sizeof(fixed)) {
                char flexible[length + 1];
                digits = flexible;
                snprintf(flexible, sizeof(flexible), "%ld", argument);
        }

        directive_number(directive, flags, width, precision, digits, length, result);
}

static void
directive_integer_bignum(unichar directive, int flags, int width, int precision, VALUE argument, VALUE result)
{
        VALUE str = rb_big2str(argument, 10);
        const char *digits = RSTRING_PTR(str);
        /* TODO: Why aren’t we passing around width and precision as longs? */
#ifdef HAVE_RB_LONG2INT
        int length = rb_long2int(RSTRING_END(str) - digits);
#else
        int length = (int)(RSTRING_END(str) - digits);
#endif

        directive_number(directive, flags, width, precision, digits, length, result);
}

static void
directive_integer(unichar directive, int flags, int width, int precision, VALUE argument, VALUE result)
{
        VALUE bignum = Qundef;
        long lvalue = directive_integer_value(argument, &bignum);

        if (bignum == Qundef)
                directive_integer_long(directive, flags, width, precision, lvalue, result);
        else
                directive_integer_bignum(directive, flags, width, precision, bignum, result);
}

static void
directive(const char **p, const char *end, struct format_arguments *arguments, VALUE result)
{
        VALUE argument = Qundef;
        bool argument_to_s = false;
        /* TODO: Use DirectiveFlags instead of int. */
        int flags = directive_flags(p, end, arguments, &argument, &argument_to_s);
        if (argument_to_s) {
                directive_validate_flags('s', flags, DIRECTIVE_FLAGS_MINUS);
                directive_string('s', flags, 0, 0, argument, result);
                return;
        }

        int width = directive_width(p, end, arguments, &flags);

        int precision = directive_precision(p, end);

        unichar c = _rb_u_aref_char_validated(*p, end);
        *p = u_next(*p);
        switch (c) {
        case '%':
                directive_validate_flags(c, flags, DIRECTIVE_FLAGS_NONE);
                directive_validate_argument_not_given(c, argument);
                directive_validate_width_not_given(c, width);
                directive_validate_precision_not_given(c, precision);
                directive_escape(c, result);
                return;
        default:
                break;
        }

        /* TODO: Should MINUS be legal without a width? */
        static struct {
                unichar c;
                int flags;
                bool width;
                bool precision;
                void (*f)(unichar c, int, int, int, VALUE, VALUE);
        } directives[] = {
                { 'c', DIRECTIVE_FLAGS_MINUS, true, false, directive_character },
                { 's', DIRECTIVE_FLAGS_MINUS, true, true, directive_string },
                { 'p', DIRECTIVE_FLAGS_MINUS, true, true, directive_inspect },
                { 'd', DIRECTIVE_FLAGS_NUMBER, true, true, directive_integer },
                { 'i', DIRECTIVE_FLAGS_NUMBER, true, true, directive_integer },
                { 'u', DIRECTIVE_FLAGS_NUMBER, true, true, directive_integer }
        };

        for (size_t i = 0; i < lengthof(directives); i++)
                if (directives[i].c == c) {
                        directive_validate_flags(c, flags, directives[i].flags);
                        if (!directives[i].width)
                                directive_validate_width_not_given(c, width);
                        if (!directives[i].precision)
                                directive_validate_precision_not_given(c, precision);
                        directives[i].f(c,
                                        flags,
                                        width,
                                        precision,
                                        argument == Qundef ?
                                                format_arguments_next(arguments) :
                                                argument,
                                        result);
                        return;
                }


        rb_raise(rb_eArgError, "unknown directive: %lc", c);
}

VALUE
rb_u_string_format(int argc, const VALUE *argv, VALUE self)
{
        const UString *string = RVAL2USTRING(self);
        const char *p = USTRING_STR(string);
        const char *end = USTRING_END(string);

        struct format_arguments arguments = {
                .argc = argc,
                .argv = argv,
                .i = 0,
                .absolute = false,
                .names = Qundef
        };

        VALUE result = rb_u_buffer_new_sized(127);

        while (p < end) {
                const char *q = p;

                while (q < end && *q != '%')
                        q++;

                rb_u_buffer_append(result, p, q - p);

                if (q == end)
                        break;

                p = q + 1;

                directive(&p, end, &arguments, result);
        }

        return rb_u_buffer_to_u_bang(result);
}

VALUE
rb_u_string_format_m(VALUE self, VALUE argument)
{
        /* TODO: Why volatile? */
        volatile VALUE tmp = rb_check_array_type(argument);

        if (!NIL_P(tmp))
                /* TODO: USE RARRAY_LENINT */
                return rb_u_string_format(RARRAY_LEN(tmp), RARRAY_PTR(tmp), self);

        return rb_u_string_format(1, &argument, self);
}
