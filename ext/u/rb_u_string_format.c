#include "rb_includes.h"
#include <limits.h>
#include <math.h>
#ifdef HAVE_RUBY_INTERN_H
#  include <ruby/intern.h>
#else
#  include <intern.h>
#endif
#ifdef HAVE_RUBY_ENCODING_H
#  include <ruby/encoding.h>
#endif
#include "rb_u_buffer.h"
#include "rb_u_string_to_inum.h"

enum directive_flags {
        DIRECTIVE_FLAGS_NONE = 0,
        DIRECTIVE_FLAGS_SPACE = 1,
        DIRECTIVE_FLAGS_SHARP = 2,
        DIRECTIVE_FLAGS_PLUS = 4,
        DIRECTIVE_FLAGS_MINUS = 8,
        DIRECTIVE_FLAGS_ZERO = 16,
        DIRECTIVE_FLAGS_DECIMAL =
                DIRECTIVE_FLAGS_SPACE |
                DIRECTIVE_FLAGS_PLUS |
                DIRECTIVE_FLAGS_MINUS |
                DIRECTIVE_FLAGS_ZERO,
        DIRECTIVE_FLAGS_NUMBER =
                DIRECTIVE_FLAGS_DECIMAL |
                DIRECTIVE_FLAGS_SHARP
};

struct format_arguments {
        int argc;
        const VALUE *argv;
        int i;
        bool absolute;
        VALUE names;
};

#if !(defined(HAVE_RB_LONG2INT) || defined(rb_long2int))
#  if SIZEOF_INT < SIZEOF_LONG
static void
rb_out_of_int(long l)
{
        rb_u_raise(rb_eRangeError,
                   l < 0 ?
                        "integer %ld too small to convert to C type int" :
                        "integer %ld too big to convert to C type int",
                   l);
}
#    if defined(__GNUC__) && __GNUC__ > 2
#      define rb_long2int(l) __extension__({ \
        long _rb_long2int_l = (l); \
        int _rb_long2int_i = (int)_rb_long2int_l; \
        if ((long)_rb_long2int_i != _rb_long2int_l) \
                rb_out_of_int(_rb_long2int_l); \
        _rb_long2int_i; \
})
#    else
static inline int
rb_long2int(long l)
{
        int i = (int)l;

        if ((long)i != l)
                rb_out_of_int(l);

        return i;
}
#    endif
#  else
#    define rb_long2int(l) ((int)(l))
#  endif
#endif

#ifndef RARRAY_LENINT
#  define RARRAY_LENINT(ary) rb_long2int(RARRAY_LEN(ary))
#endif

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
                uint32_t c = _rb_u_dref(q, end);

                if (!u_char_isdigit(c)) {
                        *p = q;
                        return n;
                }

                q = u_next(q);

                int m = 10 * n + u_char_digit_value(c);
                if (m / 10 != n) {
                        while (q < end && u_char_isdigit(u_dref_validated_n(q, end - q)))
                                q = u_next(q);
                        rb_u_raise(rb_eArgError,
                                   "%s too large: %*s > %d",
                                   type, (int)(q - *p), *p, INT_MAX);
                }

                n = m;
        }

        rb_u_raise(rb_eArgError, "directive missing after %s", type);
}

static bool
directive_argument_number(const char **p, const char *end, const char *type,
                          int *argument_number)
{
        if (*argument_number != 0)
                rb_u_raise(rb_eArgError, "%s already given", type);

        const char *q = *p;
        int n = directive_parse_int(&q, end, type);
        if (*q != '$')
                return false;
        *p = u_next(q);
        *argument_number = n;

        if (*p == end)
                rb_u_raise(rb_eArgError, "directive missing after %s", type);

        return true;
}

static void
directive_argument_name(const char **p, const char *end, char right,
                        ID *argument_id)
{
        if (*argument_id != 0)
                rb_u_raise(rb_eArgError, "argument name already given");

        const char *q = *p;

        while (q < end && *q != right)
                q = rb_u_next_validated(q, end);

        if (q == end)
                rb_u_raise(rb_eArgError,
                           "missing argument name end delimiter ‘%c’: %s",
                           right, *p);

        const char *base = u_next(*p);
        long length = q - base;
#ifdef HAVE_RUBY_ENCODING_H
        *argument_id = rb_intern3(base, length, rb_utf8_encoding());
#else
        char name[length + 1];
        memcpy(name, base, length);
        name[length] = '\0';
        *argument_id = rb_intern(name);
#endif

        *p = rb_u_next_validated(q, end);

        if (*p == end)
                rb_u_raise(rb_eArgError, "directive missing after argument name");
}

static VALUE
format_arguments_absolute(struct format_arguments *arguments, int absolute)
{
        if (arguments->i > 0)
                rb_u_raise(rb_eArgError,
                           "cannot use absolute argument number %d: relative argument number already used",
                           absolute);

        if (arguments->names != Qundef)
                rb_u_raise(rb_eArgError,
                           "cannot use absolute argument number %d: named argument already used",
                           absolute);

        arguments->absolute = true;

        if (absolute > arguments->argc)
                rb_u_raise(rb_eArgError,
                           "absolute argument number beyond end of argument list: %d > %d",
                           absolute, arguments->argc);

        return arguments->argv[absolute - 1];
}

static VALUE
format_arguments_id(struct format_arguments *arguments, ID id)
{
        if (arguments->i > 0)
                rb_u_raise(rb_eArgError,
                           "cannot use named argument “%s”: relative argument number already used",
                           rb_id2name(id));

        if (arguments->absolute)
                rb_u_raise(rb_eArgError,
                           "cannot use named argument “%s”: absolute argument number already used",
                           rb_id2name(id));

        if (arguments->names == Qundef) {
                VALUE tmp;

                if (arguments->argc != 1 ||
                    NIL_P(tmp = rb_check_convert_type(arguments->argv[0], T_HASH, "Hash", "to_hash")))
                        rb_u_raise(rb_eArgError,
                                   "one Hash argument required when using named arguments in format");

                arguments->names = tmp;
        }

        VALUE argument = rb_hash_lookup2(arguments->names, ID2SYM(id), Qundef);
        if (argument == Qundef)
                rb_u_raise(rb_eKeyError, "named argument not found: %s", rb_id2name(id));

        return argument;
}

static VALUE
format_arguments_next(struct format_arguments *arguments)
{
        if (arguments->absolute)
                rb_u_raise(rb_eArgError,
                           "cannot use positional argument numbers after absolute argument numbers");

        if (arguments->names != Qundef)
                rb_u_raise(rb_eArgError,
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
                uint32_t c = _rb_u_dref(*p, end);

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
                                rb_u_raise(rb_eArgError,
                                           "cannot use absolute argument number: argument name already given");
                        continue;
                case '<':
                        if (argument_number != 0)
                                rb_u_raise(rb_eArgError,
                                           "cannot use argument name: absolute argument number already given");
                        directive_argument_name(p, end, '>', &argument_id);
                        *argument_to_s = false;
                        continue;
                case '{':
                        if (argument_number != 0)
                                rb_u_raise(rb_eArgError,
                                           "cannot use argument name: absolute argument number already given");
                        directive_argument_name(p, end, '}', &argument_id);
                        *argument_to_s = true;
                        goto setup_argument;
                default:
                        goto setup_argument;
                }

                if (flags & flag)
                        rb_warning("repeated flag in format: ‘%c’", c);
                flags |= flag;

                *p = u_next(*p);
        }

        if (flags != DIRECTIVE_FLAGS_NONE && *p == end)
                rb_u_raise(rb_eArgError, "directive missing after flags");

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
                enum directive_flags *flags)
{
        if (*p == end)
                return 0;

        uint32_t c = _rb_u_dref(*p, end);

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
        if (*p == end)
                return -1;

        uint32_t c = _rb_u_dref(*p, end);

        if (c != '.')
                return -1;

        *p = u_next(*p);

        return directive_parse_int(p, end, "field precision");
}

static void
directive_validate_flags(uint32_t c, int flags, int valid)
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

        char buf[U_CHAR_MAX_BYTE_LENGTH];
        int length = u_char_to_u(c, buf);
        if (n == 1)
                rb_u_raise(rb_eArgError,
                           "invalid flag ‘%s’ given to directive ‘%.*s’",
                           invalid, length, buf);

        rb_u_raise(rb_eArgError,
                   "invalid flags “%s” given to directive ‘%.*s’",
                   invalid, length, buf);
}

NORETURN(static void
         directive_simple_error(uint32_t c, const char *message))
{
        char buf[U_CHAR_MAX_BYTE_LENGTH];
        int length = u_char_to_u(c, buf);
        rb_u_raise(rb_eArgError, "%s: %.*s", message, length, buf);
}

static void
directive_validate_argument_not_given(uint32_t c, VALUE argument)
{
        if (argument != Qundef)
                directive_simple_error(c, "directive does not take an argument");
}

static void
directive_validate_width_not_given(uint32_t c, int width)
{
        if (width != 0)
                directive_simple_error(c, "directive does not allow specifying a width");
}

static void
directive_validate_precision_not_given(uint32_t c, int precision)
{
        if (precision >= 0)
                directive_simple_error(c, "directive does not allow specifying a precision");
}

static void
directive_escape(uint32_t c, VALUE result)
{
        rb_u_buffer_append_char(result, c);
}

static void
directive_pad(int flags, int padding, const char *str, long length, VALUE result)
{
        if (flags & DIRECTIVE_FLAGS_MINUS) {
                rb_u_buffer_append(result, str, length);
                rb_u_buffer_append_char_n(result, ' ', padding);
        } else {
                rb_u_buffer_append_char_n(result, ' ', padding);
                rb_u_buffer_append(result, str, length);
        }
}

static void
directive_character(UNUSED(uint32_t directive), int flags, int width, UNUSED(int precision), VALUE argument, VALUE result)
{
        VALUE tmp = rb_u_string_check_type(argument);

        uint32_t c;
        const char *p;
        int length;

        if (!NIL_P(tmp)) {
                const struct rb_u_string *string = RVAL2USTRING_ANY(tmp);
                p = USTRING_STR(string);
                c = _rb_u_dref(p, USTRING_END(string));
                length = (int)(u_next(p) - p);
        } else {
                char buf[U_CHAR_MAX_BYTE_LENGTH];
                p = buf;
                c = NUM2INT(argument);
                length = rb_u_char_to_u(c, buf);
        }

        int padding = width - (int)u_char_width(c);
        if (padding < 0) {
                rb_u_buffer_append_char(result, c);
                return;
        }

        directive_pad(flags, padding, p, length, result);
}

static void
directive_string(UNUSED(uint32_t directive), int flags, int width, int precision, VALUE argument, VALUE result)
{
        VALUE str = rb_u_string_object_as_string(argument);

        if (OBJ_TAINTED(str))
                OBJ_TAINT(result);

        const struct rb_u_string *string = RVAL2USTRING_ANY(str);
        const char *p = USTRING_STR(string);
        long length = USTRING_LENGTH(string);

        if (precision > 0) {
                int i = 0;
                const char *q = p, *end = p + length;
                while (i < precision && q < end) {
                        i += (int)u_char_width(_rb_u_dref(q, end));
                        q = u_next(q);
                }
                length = q - p;
        }

        long n_cells;
        if (width == 0 || width < (n_cells = u_width_n(p, length))) {
                rb_u_buffer_append(result, p, length);
                return;
        }

        directive_pad(flags, width - (int)n_cells, p, length, result);
}

static void
directive_inspect(uint32_t directive, int flags, int width, int precision, VALUE argument, VALUE result)
{
        directive_string(directive, flags, width, precision, rb_inspect(argument), result);
}

static long
directive_integer_value_m(VALUE argument, VALUE *bignum)
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
                return directive_integer_value_m(rb_str_to_inum(argument, 0, true), bignum);
        case T_BIGNUM:
                *bignum = argument;
                return 0;
        case T_FIXNUM:
                return FIX2LONG(argument);
        default:
                if (RTEST(rb_obj_is_kind_of(argument, rb_cUString)))
                        return directive_integer_value_m(rb_u_string_to_inum(argument, 0, true), bignum);
                return directive_integer_value_m(rb_Integer(argument), bignum);
        }
}

static long
directive_integer_value(VALUE argument, int base, VALUE *bignum)
{
        long value = directive_integer_value_m(argument, bignum);
        if (base == 2 && *bignum == Qundef)
                return directive_integer_value_m(rb_int2big(value), bignum);
        return value;
}

static void
directive_number_output(int flags, int width, int precision,
                        const char *prefix, uint32_t precision_filler, const char *digits, int length,
                        VALUE result)
{
        int prefix_length = (int)strlen(prefix);
        width -= prefix_length;

        if (precision >= 0)
                flags &= ~DIRECTIVE_FLAGS_ZERO;

        if (precision < length)
                precision = length;
        width -= precision;

        if (!(flags & DIRECTIVE_FLAGS_MINUS) && !(flags & DIRECTIVE_FLAGS_ZERO))
                rb_u_buffer_append_char_n(result, ' ', width);

        rb_u_buffer_append(result, prefix, prefix_length);

        if (!(flags & DIRECTIVE_FLAGS_MINUS) && (flags & DIRECTIVE_FLAGS_ZERO))
                rb_u_buffer_append_char_n(result, '0', width);

        rb_u_buffer_append_char_n(result, precision_filler, precision - length);

        rb_u_buffer_append(result, digits, length);

        if (flags & DIRECTIVE_FLAGS_MINUS)
                rb_u_buffer_append_char_n(result, ' ', width);
}

#define BITS2DECIMALDIGITS(n) (((long)(n) * 146) / 485 + 1) /* lg(10)⁻¹ ≈ 146/485 */
#define BITS2OCTALDIGITS(n) (((long)(n) * 1) / 3 + 1) /* lg(8)⁻¹ = 3 */

#define DIGITS_BUFFER_SIZE (BITS2OCTALDIGITS(sizeof(long) * CHAR_BIT) + 1)

#define BASE2FORMAT(base) \
        ((base) == 10 ? "%ld" : ((base) == 16 ? "%lx" : "%lo"))

static void
directive_conflicting_flags_warning(uint32_t directive, int ignored, int when)
{
        char buf[U_CHAR_MAX_BYTE_LENGTH];
        int length = u_char_to_u(directive, buf);
        rb_warning("‘%.*s’ directive ignores ‘%c’ flag when ‘%c’ flag has been specified",
                   length, buf, ignored, when);
}

static bool
directive_number_sign(uint32_t directive, bool negative, int flags, char *sign)
{
        if (flags & DIRECTIVE_FLAGS_PLUS && flags & DIRECTIVE_FLAGS_SPACE)
                directive_conflicting_flags_warning(directive, ' ', '+');

        if (negative) {
                sign[0] = '-';
                return true;
        }

        if (flags & DIRECTIVE_FLAGS_PLUS)
                sign[0] = '+';
        else if (flags & DIRECTIVE_FLAGS_SPACE)
                sign[0] = ' ';
        else
                sign[0] = '\0';

        return false;
}

static inline int
directive_number_long_signed(uint32_t directive, int flags, long argument,
                             int base, char *sign, const char **digits, char *buffer)
{
        if (directive_number_sign(directive, argument < 0, flags, sign))
                argument = -argument;

        *digits = buffer;
        return snprintf(buffer, DIGITS_BUFFER_SIZE, BASE2FORMAT(base), argument);
}

static inline int
directive_number_bignum_signed(uint32_t directive, int flags, VALUE argument,
                               int base, char *sign, const char **digits, VALUE *str)
{
        *str = rb_big2str(argument, base);
        *digits = RSTRING_PTR(*str);
        if (directive_number_sign(directive, *digits[0] == '-', flags, sign))
                (*digits)++;

        return rb_long2int(RSTRING_END(*str) - *digits);
}

static void
directive_number_check_flags(uint32_t directive, int flags, int precision)
{
        if ((flags & DIRECTIVE_FLAGS_MINUS) && (flags & DIRECTIVE_FLAGS_ZERO))
                directive_conflicting_flags_warning(directive, '0', '-');

        if (precision >= 0 && (flags & DIRECTIVE_FLAGS_ZERO)) {
                char buf[U_CHAR_MAX_BYTE_LENGTH];
                int length = u_char_to_u(directive, buf);
                rb_warning("‘%.*s’ directive ignores ‘0’ flag when precision (%d) has been specified",
                           length, buf, precision);
        }
}

static int
directive_signed_number(uint32_t directive, int flags, int precision, VALUE argument,
                        int base, char *sign, const char **digits, char *buffer, VALUE *str)
{
        directive_number_check_flags(directive, flags, precision);

        VALUE bignum = Qundef;
        long lvalue = directive_integer_value(argument, base, &bignum);

        return (bignum == Qundef) ?
                directive_number_long_signed(directive, flags, lvalue, base, sign, digits, buffer) :
                directive_number_bignum_signed(directive, flags, bignum, base, sign, digits, str);
}

static const char *
directive_number_skip_bits(const char *digits, int base)
{
        const char *p = digits;

        if (base == 16)
                while (*p == 'f' || *p == 'F')
                        p++;
        else if (base == 8) {
                p++;
                while (*p == '7')
                        p++;
        } else if (base == 2)
                while (*p == '1')
                        p++;

        return p - 1;
}

static inline int
directive_number_long_unsigned(long argument,
                               int base, char *prefix, const char **digits, char *buffer)
{
        *digits = buffer;
        int length = snprintf(buffer, DIGITS_BUFFER_SIZE, BASE2FORMAT(base), (unsigned long)argument);

        if (argument < 0) {
                *digits = directive_number_skip_bits(buffer, base);
                length -= (int)(*digits - buffer);
                strcat(prefix, "..");
        }

        return length;
}

static inline int
directive_number_bignum_unsigned(VALUE argument,
                                 int base, char *prefix, const char **digits, VALUE *str)
{
        if (!RBIGNUM_SIGN(argument)) {
                argument = rb_big_clone(argument);
                rb_big_2comp(argument);
        }

        *str = rb_big2str0(argument, base, RBIGNUM_SIGN(argument));
        *digits = RSTRING_PTR(*str);
        if (*digits[0] == '-') {
                *digits = directive_number_skip_bits(*digits + 1, base);
                strcat(prefix, "..");
        }

        return rb_long2int(RSTRING_END(*str) - *digits);
}

static inline int
directive_unsigned_number(uint32_t directive, int flags, int precision, VALUE argument,
                          int base, char *prefix, const char **digits, char *buffer, VALUE *str)
{
        directive_number_check_flags(directive, flags, precision);

        VALUE bignum = Qundef;
        long lvalue = directive_integer_value(argument, base, &bignum);

        return (bignum == Qundef) ?
                directive_number_long_unsigned(lvalue, base, prefix, digits, buffer) :
                directive_number_bignum_unsigned(bignum, base, prefix, digits, str);
}

static int
directive_signed_or_unsigned_number(uint32_t directive, int flags, int precision, VALUE argument,
                                    int base, char *prefix, const char **digits, char *buffer, VALUE *str)
{
        if (!(flags & DIRECTIVE_FLAGS_SHARP))
                for (char *p = prefix; *p != '\0'; p++)
                        *p = '\0';

        if (!(flags & (DIRECTIVE_FLAGS_PLUS | DIRECTIVE_FLAGS_SPACE)))
                return directive_unsigned_number(directive, flags, precision, argument, base, prefix, digits, buffer, str);

        /* Move prefix forward one position to make room for sign. */
        for (char *p = prefix + strlen(prefix); p > prefix; p--)
                *p = *(p - 1);

        return directive_signed_number(directive, flags, precision, argument, base, prefix, digits, buffer, str);
}

static void
directive_integer(uint32_t directive, int flags, int width, int precision, VALUE argument, VALUE result)
{
        char sign[] = "\0\0";
        char buffer[DIGITS_BUFFER_SIZE];
        VALUE str;
        const char *digits;
        int length = directive_signed_number(directive, flags, precision, argument, 10, sign, &digits, buffer, &str);

        directive_number_output(flags, width, precision, sign, '0', digits, length, result);
}

static bool
directive_number_is_unsigned(char *prefix)
{
        return strstr(prefix, "..") != NULL;
}

static void
directive_ignored_flag_on_negative_argument_warning(uint32_t directive, int ignored)
{
        char buf[U_CHAR_MAX_BYTE_LENGTH];
        int length = u_char_to_u(directive, buf);
        rb_warning("‘%.*s’ directive ignores ‘%c’ flag when given a negative argument",
                   length, buf, ignored);
}

static void
directive_unsigned_number_output(uint32_t directive, int flags, int width, int precision,
                                 char *prefix, const char *digits, int length,
                                 VALUE result)
{
        if (directive_number_is_unsigned(prefix)) {
                if (flags & DIRECTIVE_FLAGS_ZERO)
                        directive_ignored_flag_on_negative_argument_warning(directive, '0');

                directive_number_output(flags & ~DIRECTIVE_FLAGS_ZERO,
                                        width,
                                        precision < 0 ? precision :
                                                (precision - 2 >= 0 ? precision - 2 : 0),
                                        prefix, digits[0], digits, length,
                                        result);
        } else
                directive_number_output(flags, width, precision, prefix, '0', digits, length, result);

}

static void
directive_octal(uint32_t directive, int flags, int width, int precision, VALUE argument, VALUE result)
{
        char prefix[] = "0\0\0\0\0";
        char buffer[DIGITS_BUFFER_SIZE];
        VALUE str;
        const char *digits;
        int length = directive_signed_or_unsigned_number(directive, flags, precision, argument, 8, prefix, &digits, buffer, &str);

        if ((flags & DIRECTIVE_FLAGS_SHARP) &&
            (precision >= 0 ||
             directive_number_is_unsigned(prefix) ||
             (length == 1 && digits[0] == '0'))) {
                if (directive_number_is_unsigned(prefix))
                        directive_ignored_flag_on_negative_argument_warning(directive, '#');

                for (char *p = prefix; *p != '\0'; p++)
                        *p = *(p + 1);
        }

        directive_unsigned_number_output(directive, flags, width, precision, prefix, digits, length, result);
}

static void
directive_hexadecimal(uint32_t directive, int flags, int width, int precision, VALUE argument, VALUE result)
{
        char prefix[] = "0x\0\0\0\0";
        if (directive == 'X')
                prefix[1] = 'X';
        char buffer[DIGITS_BUFFER_SIZE];
        VALUE str;
        const char *digits;
        int length = directive_signed_or_unsigned_number(directive, flags, precision, argument, 16, prefix, &digits, buffer, &str);

        if ((flags & DIRECTIVE_FLAGS_SHARP) && (length == 1 && digits[0] == '0'))
                for (char *p = prefix; *p != '\0'; p++)
                        *p = '\0';

        if (directive == 'X')
                for (char *p = (char *)digits; *p != '\0'; p++)
                        *p = u_char_upcase(*p);

        directive_unsigned_number_output(directive, flags, width, precision, prefix, digits, length, result);
}

static void
directive_binary(uint32_t directive, int flags, int width, int precision, VALUE argument, VALUE result)
{
        char prefix[] = "0b\0\0\0\0";
        if (directive == 'B')
                prefix[1] = 'B';
        char buffer[DIGITS_BUFFER_SIZE];
        VALUE str;
        const char *digits;
        int length = directive_signed_or_unsigned_number(directive, flags, precision, argument, 2, prefix, &digits, buffer, &str);

        if ((flags & DIRECTIVE_FLAGS_SHARP) && (length == 1 && digits[0] == '0'))
                for (char *p = prefix; *p != '\0'; p++)
                        *p = '\0';

        directive_unsigned_number_output(directive, flags, width, precision, prefix, digits, length, result);
}

static inline void
directive_float_nan(uint32_t directive, int flags, int width, VALUE result)
{
        /* sign? + NaN + \0 */
        char buffer[1 + 3 + 1] = "\0";
        int length = 3;

        directive_number_sign(directive, false, flags, buffer);
        if (buffer[0] != '\0')
                length++;

        strcat(buffer, "NaN");

        directive_pad(flags, width - length, buffer, length, result);
}

static inline void
directive_float_inf(uint32_t directive, int flags, int width, double argument, VALUE result)
{
        /* sign? + Inf + \0 */
        char buffer[1 + 3 + 1] = "\0";
        int length = 3;

        directive_number_sign(directive, argument < 0.0, flags, buffer);
        if (buffer[0] != '\0')
                length++;

        strcat(buffer, "Inf");

        directive_pad(flags, width - length, buffer, length, result);
}

#pragma GCC diagnostic ignored "-Wformat-nonliteral"
static void
directive_float_format(uint32_t directive, int flags, int width, int precision, double argument, VALUE result)
{
        char format[1 +                                                 /* '%' */
                    5 +                                                 /* flags{0,5} */
                    BITS2DECIMALDIGITS(sizeof(width) * CHAR_BIT) +      /* width_digits? */
                    1 +                                                 /* ('.' */
                    BITS2DECIMALDIGITS(sizeof(precision) * CHAR_BIT) +  /*  precision_digits)? */
                    1 +                                                 /* directive */
                    1];                                                 /* '\0' */
        char *p = format;
        const char *end = format + lengthof(format);

        *p++ = '%';
        if (flags & DIRECTIVE_FLAGS_SHARP)
                *p++ = '#';
        if (flags & DIRECTIVE_FLAGS_PLUS)
                *p++ = '+';
        if (flags & DIRECTIVE_FLAGS_MINUS)
                *p++ = '-';
        if (flags & DIRECTIVE_FLAGS_ZERO)
                *p++ = '0';
        if (flags & DIRECTIVE_FLAGS_SPACE)
                *p++ = ' ';

        if (width > 0)
                p += snprintf(p, end - p, "%d", width);

        if (precision >= 0)
                p += snprintf(p, end - p, ".%d", precision);

        *p++ = directive;
        *p = '\0';

        int exponent = 0;
        frexp(argument, &exponent);
        /* sign? +
         * prefix? +
         * character-before-separator? +
         * (decimal_digits or characters after exponent) +
         * separator? +
         * precision? +
         * exponent-char?
         * exponent-±?
         */
        size_t needed = 1 +
                2 +
                1 +
                abs((int)BITS2DECIMALDIGITS(exponent)) +
                1 +
                (size_t)(precision >= 0 ? precision : 0) +
                1 +
                1;
        if (needed < (size_t)width)
                needed = width;
        needed += 1;

        rb_u_buffer_append_printf(result, needed, format, argument);
}
#pragma GCC diagnostic warning "-Wformat-nonliteral"

static void
directive_float(uint32_t directive, int flags, int width, int precision, VALUE argument, VALUE result)
{
        double value = RFLOAT_VALUE(rb_Float(argument));

        if (isnan(value))
                directive_float_nan(directive, flags, width, result);
        else if (isinf(value))
                directive_float_inf(directive, flags, width, value, result);
        else
                directive_float_format(directive, flags, width, precision, value, result);
}

static void
directive(const char **p, const char *end, struct format_arguments *arguments, VALUE result)
{
        VALUE argument = Qundef;
        bool argument_to_s = false;
        enum directive_flags flags = directive_flags(p, end, arguments, &argument, &argument_to_s);
        if (argument_to_s) {
                directive_validate_flags('s', flags, DIRECTIVE_FLAGS_MINUS);
                directive_string('s', flags, 0, 0, argument, result);
                return;
        }

        int width = directive_width(p, end, arguments, &flags);

        int precision = directive_precision(p, end);

        uint32_t c = '\0';
        if (*p < end) {
                c = _rb_u_dref(*p, end);
                *p = u_next(*p);
        }
        switch (c) {
        case '%':
        case '\0':
        case '\n':
                directive_validate_flags('%', flags, DIRECTIVE_FLAGS_NONE);
                directive_validate_argument_not_given('%', argument);
                directive_validate_width_not_given('%', width);
                directive_validate_precision_not_given('%', precision);
                directive_escape('%', result);
                if (c == '\n' || (c == '\0' && *p != end))
                        directive_escape(c, result);
                return;
        default:
                break;
        }

        static struct {
                uint32_t c;
                int flags;
                bool width;
                bool precision;
                void (*f)(uint32_t c, int, int, int, VALUE, VALUE);
        } directives[] = {
                { 'c', DIRECTIVE_FLAGS_MINUS, true, false, directive_character },
                { 's', DIRECTIVE_FLAGS_MINUS, true, true, directive_string },
                { 'p', DIRECTIVE_FLAGS_MINUS, true, true, directive_inspect },
                { 'd', DIRECTIVE_FLAGS_DECIMAL, true, true, directive_integer },
                { 'i', DIRECTIVE_FLAGS_DECIMAL, true, true, directive_integer },
                { 'u', DIRECTIVE_FLAGS_DECIMAL, true, true, directive_integer },
                { 'o', DIRECTIVE_FLAGS_NUMBER, true, true, directive_octal },
                { 'x', DIRECTIVE_FLAGS_NUMBER, true, true, directive_hexadecimal },
                { 'X', DIRECTIVE_FLAGS_NUMBER, true, true, directive_hexadecimal },
                { 'b', DIRECTIVE_FLAGS_NUMBER, true, true, directive_binary },
                { 'B', DIRECTIVE_FLAGS_NUMBER, true, true, directive_binary },
                { 'f', DIRECTIVE_FLAGS_NUMBER, true, true, directive_float },
                { 'g', DIRECTIVE_FLAGS_NUMBER, true, true, directive_float },
                { 'G', DIRECTIVE_FLAGS_NUMBER, true, true, directive_float },
                { 'e', DIRECTIVE_FLAGS_NUMBER, true, true, directive_float },
                { 'E', DIRECTIVE_FLAGS_NUMBER, true, true, directive_float },
                { 'a', DIRECTIVE_FLAGS_NUMBER, true, true, directive_float },
                { 'A', DIRECTIVE_FLAGS_NUMBER, true, true, directive_float }
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

        char buf[U_CHAR_MAX_BYTE_LENGTH];
        int length = u_char_to_u(c, buf);
        rb_u_raise(rb_eArgError, "unknown directive: %.*s", length, buf);
}

VALUE
rb_u_buffer_append_format(int argc, const VALUE *argv, VALUE self, VALUE format)
{
        const struct rb_u_string *string = RVAL2USTRING_ANY(format);
        const char *p = USTRING_STR(string);
        const char *end = USTRING_END(string);

        struct format_arguments arguments = {
                .argc = argc,
                .argv = argv,
                .i = 0,
                .absolute = false,
                .names = Qundef
        };

        while (p < end) {
                const char *q = p;

                while (q < end && *q != '%')
                        q++;

                rb_u_buffer_append(self, p, q - p);

                if (q == end)
                        break;

                p = q + 1;

                directive(&p, end, &arguments, self);
        }

        if (OBJ_TAINTED(format))
                OBJ_TAINT(self);

        return self;
}

/* @overload append_format(format, *values)
 *
 *   Appends the result of FORMAT#%(values) to the receiver.
 *
 *   @param [U::String, #to_str] format
 *   @return [self] */
VALUE
rb_u_buffer_append_format_m(int argc, const VALUE *argv, VALUE self)
{
        need_at_least_n_arguments(argc, 1);

        return rb_u_buffer_append_format(argc - 1, argv + 1, self, argv[0]);
}


VALUE
rb_u_string_format(int argc, const VALUE *argv, VALUE self)
{
        return rb_u_buffer_to_u_bang(rb_u_buffer_append_format(argc,
                                                               argv,
                                                               rb_u_buffer_new_sized(127),
                                                               self));
}

/* @overload %(value)
 *
 *   Returns a formatted string of the values in Array(VALUE) by treating the
 *   receiver as a format specification of this formatted string.
 *
 *   A format specification is a string consisting of sequences of normal
 *   characters that are copied verbatim and field specifiers.  A field
 *   specifier consists of a `%`, followed by any optional flags, an optional
 *   width, an optional precision, and a directive:
 *
 *       %[flags][width][.[precision]]directive
 *
 *   Note that this means that a lone `%` at the end of the string is simply
 *   copied verbatim as it, by this definition, isn’t a field directive.
 *
 *   The directive determines how this field should be formatted.  The flags,
 *   width, and precision modify this interpretation.
 *
 *   The field often takes a value from VALUE and formats it according to a
 *   given set of rules, which depend on the flags, width, and precision, but
 *   can also output other, hardwired, values.
 *
 *   The directives that don’t take a value are
 *
 *   <table>
 *     <thead>
 *       <tr><th>Directive</th><th>Description</th></tr>
 *     </thead>
 *     <tbody>
 *       <tr>
 *         <td>%</td>
 *         <td>Outputs ‘%’.</td>
 *       </tr>
 *       <tr>
 *         <td>\n</td>
 *         <td>Outputs “%\n”.</td>
 *       </tr>
 *       <tr>
 *         <td>\0</td>
 *         <td>Outputs “%\0”.</td>
 *       </tr>
 *     </tbody>
 *   </table>
 *
 *   None of these directives take any flags, width, or precision.
 *
 *   All of the following directives allow you to specify a width.  The width
 *   only ever limits the minimum width of the field, that is, at least _width_
 *   cells will be filled by the field, but perhaps more will actually be
 *   required in the end.
 *
 *   <dl>
 *     <dt>c</dt>
 *     <dd>
 *       <p>Outputs</p>
 *
 *       <pre><code>[left-padding]character[right-padding]</code></pre>
 *
 *       <p>If a width <em>w</em> has been specified and the
 *       ‘<code>-</code>’ flag hasn’t been given, <em>left-padding</em>
 *       consists of enough spaces to make the whole field at least <em>w</em>
 *       cells wide, otherwise it’s empty.</p>
 *
 *       <p><em>Character</em> is the result of #to_str#chr on the
 *       argument, if it responds to #to_str, otherwise it’s the result of
 *       #to_int turned into a string containing the character at that code
 *       point.  A precision isn’t allowed.  The {#width} of the character is
 *       used in any width calculations.</p>
 *
 *       <p>If a width <em>w</em> has been specified and the ‘<code>-</code>’
 *       flag has been given, <em>right-padding</em> consists of enough spaces
 *       to make the whole field at least <em>w</em> cells wide, otherwise it’s
 *       empty.</p>
 *     </dd>
 *     <dt>s</dt>
 *     <dd>
 *       <p>Outputs</p>
 *
 *       <pre><code>[left-padding]string[right-padding]</code></pre>
 *
 *       <p><em>Left-padding</em> and <em>right-padding</em> are the same as
 *       for the ‘c’ directive described above.</p>
 *
 *       <p><em>String</em> is a substring of the result of #to_s on the
 *       argument that is <em>w</em> cells wide, where <em>w</em> = precision,
 *       if a precision has been specified, <em>w</em> = {#width}
 *       otherwise.</p>
 *     </dd>
 *     <dt>p</dt>
 *     <dd>
 *       <p>Outputs</p>
 *
 *       <pre><code>[left-padding]inspect[right-padding]</code></pre>
 *
 *       <p><em>Left-padding</em> and <em>right-padding</em> are the same as
 *       for the ‘c’ directive described above.</p>
 *
 *       <p><em>String</em> is a substring of the result of #inspect on the
 *       argument that is <em>w</em> cells wide, where <em>w</em> = precision,
 *       if a precision has been specified, <em>w</em> = {#width}
 *       otherwise.</p>
 *     </dd>
 *     <dt>d</dt>
 *     <dt>i</dt>
 *     <dt>u</dt>
 *     <dd>
 *       <p>Outputs</p>
 *
 *       <pre><code>[left-padding][prefix/sign][zeroes]
 *       [precision-filler]digits[right-padding]</code></pre>
 *
 *       <p>If a width <em>w</em> has been specified and neither the
 *       ‘<code>-</code>’ nor the ‘<code>0</code>’ flag has been given,
 *       <em>left-padding</em> consists of enough spaces to make the whole
 *       field at least <em>w</em> cells wide, otherwise it’s empty.</p>
 *
 *       <p><em>Prefix/sign</em> is “-” if the argument is negative, “+” if the
 *       ‘<code>+</code>’ flag was given, and “ ” if the ‘<code> </code>’ flag
 *       was given, otherwise it’s empty.</p>
 *
 *       <p>If a width <em>w</em> has been specified and the ‘<code>0</code>’
 *       flag has been given and neither the ‘<code>-</code>’ flag has been
 *       given nor a precision has been specified, <em>zeroes</em> consists of
 *       enough zeroes to make the whole field at least <em>w</em> cells wide,
 *       otherwise it’s empty.</p>
 *
 *       <p>If a precision <em>p</em> has been specified,
 *       <em>precision-filler</em> consists of enough zeroes to make for
 *       <em>p</em> digits of output, otherwise it’s empty.</p>
 *
 *       <p><em>Digits</em> consists of the digits in base 10 that represent
 *       the result of calling Integer with the argument as its argument.</p>
 *
 *       <p>If a width <em>w</em> has been specified and the ‘<code>-</code>’
 *       flag has been given, <em>right-padding</em> consists of enough spaces
 *       to make the whole field at least <em>w</em> cells wide, otherwise it’s
 *       empty.</p>
 *
 *       <table>
 *         <thead><tr><th>Flag</th><th>Description</th></tr></thead>
 *         <tbody>
 *           <tr>
 *             <td>(Space)</td>
 *             <td>Add a “ ” prefix to non-negative numbers</td>
 *           </tr>
 *           <tr>
 *             <td><code>+</code></td>
 *             <td>Add a “+” sign to non-negative numbers; overrides the
 *             ‘<code> </code>’ flag</td>
 *           </tr>
 *           <tr>
 *             <td><code>0</code></td>
 *             <td>Use ‘0’ for any width padding; ignored when a precision has
 *             been specified</td>
 *           </tr>
 *           <tr>
 *             <td><code>-</code></td>
 *             <td>Left justify the output with ‘ ’ as padding; overrides the
 *             ‘<code>0</code>’ flag</td>
 *           </tr>
 *         </tbody>
 *       </table>
 *     </dd>
 *     <dt>o</dt>
 *     <dd>
 *       <p>Outputs</p>
 *
 *       <pre><code>[left-padding][prefix/sign][zeroes/sevens]
 *       [precision-filler]octal-digits[right-padding]</code></pre>
 *
 *       <p>If a width <em>w</em> has been specified and neither the
 *       ‘<code>-</code>’ nor the ‘<code>0</code>’ flag has been given,
 *       <em>left-padding</em> consists of enough spaces to make the whole
 *       field at least <em>w</em> cells wide, otherwise it’s empty.</p>
 *
 *       <p><em>Prefix/sign</em> is “-” if the argument is negative and the
 *       ‘<code>+</code>’ or ‘<code> </code>’ flag was given, “..” if the
 *       argument is negative, “+” if the ‘<code>+</code>’ flag was given, and
 *       “ ” if the ‘<code> </code>’ flag was given, otherwise it’s empty.</p>
 *
 *       <p>If a width <em>w</em> has been specified and the ‘<code>0</code>’
 *       flag has been given and neither the ‘<code>-</code>’ flag has been
 *       given nor a precision has been specified, <em>zeroes/sevens</em>
 *       consists of enough zeroes, if the argument is non-negative or if the
 *       ‘<code>+</code>’ or ‘<code> </code>’ flag has been specified, sevens
 *       otherwise, to make the whole field at least <em>w</em> cells wide,
 *       otherwise it’s empty.</p>
 *
 *       <p>If a precision <em>p</em> has been specified,
 *       <em>precision-filler</em> consists of enough zeroes, if the argument
 *       is non-negative or if the ‘<code>+</code>’ or ‘<code> </code>’ flag
 *       has been specified, sevens otherwise, to make for <em>p</em> digits of
 *       output, otherwise it’s empty.</p>
 *
 *       <p><em>Octal-digits</em> consists of the digits in base 8 that
 *       represent the result of #to_int on the argument, using ‘0’ through
 *       ‘7’.  A negative value will be output as a two’s complement value.</p>
 *
 *       <p>If a width <em>w</em> has been specified and the ‘<code>-</code>’
 *       flag has been given, <em>right-padding</em> consists of enough spaces
 *       to make the whole field at least <em>w</em> cells wide, otherwise it’s
 *       empty.</p>
 *
 *       <table>
 *         <thead><tr><th>Flag</th><th>Description</th></tr></thead>
 *         <tbody>
 *           <tr>
 *             <td>(Space)</td>
 *             <td>Add a “ ” prefix to non-negative numbers and don’t output
 *             negative numbers as two’s complement values</td>
 *           </tr>
 *           <tr>
 *             <td><code>+</code></td>
 *             <td>Add a “+” sign to non-negative numbers and don’t output
 *             negative numbers as two’s complement values; overrides the
 *             ‘<code> </code>’ flag</td>
 *           </tr>
 *           <tr>
 *             <td><code>0</code></td>
 *             <td>Use ‘0’ for any width padding; ignored when a precision has
 *             been specified</td>
 *           </tr>
 *           <tr>
 *             <td><code>-</code></td>
 *             <td>Left justify the output with ‘ ’ as padding; overrides the
 *             ‘<code>0</code>’ flag</td>
 *           </tr>
 *           <tr>
 *             <td><code>#</code></td>
 *             <td>Increase precision to include as many digits as necessary to
 *             make the first digit ‘0’, but don’t include the ‘0’ itself</td>
 *           </tr>
 *         </tbody>
 *       </table>
 *     </dd>
 *     <dt>x</dt>
 *     <dd>
 *       <p>Outputs</p>
 *
 *       <pre><code>[left-padding][sign][base-prefix][prefix][zeroes/fs]
 *       [precision-filler]hexadecimal-digits[right-padding]</code></pre>
 *
 *       <p><em>Left-padding</em> and <em>right-padding</em> are the same as
 *       for the ‘o’ directive described above.  <em>Zeroes/fs</em> is the same
 *       as <em>zeroes/sevens</em> for the ‘o’ directive, except that it uses
 *       ‘f’ characters instead of sevens.  The same goes for
 *       <em>precision-filler</em>.</p>
 *
 *       <p><em>Sign</em> is “-” if the argument is negative and the
 *       ‘<code>+</code>’ or ‘<code> </code>’ flag was given, “+” if the
 *       argument is non-negative and the ‘<code>+</code>’ flag was given, and
 *       “ ” if the argument is non-negative and the ‘<code> </code>’ flag was
 *       given, otherwise it’s empty.</p>
 *
 *       <p><em>Base-prefix</em> is “0x” if the ‘<code>#</code>’ flag was given
 *       and the result of #to_int on the argument is non-zero.</p>
 *
 *       <p><em>Prefix</em> is “..” if the argument is negative and neither the
 *       ‘<code>+</code>’ nor the ‘<code> </code>’ flag was given.</p>
 *
 *       <p><em>Hexadecimal-digits</em> consists of the digits in base 16 that
 *       represent the result of #to_int on the argument, using ‘0’ through ‘9’
 *       and ‘a’ through ‘f’.  A negative value will be output as a two’s
 *       complement value.</p>
 *
 *       <table>
 *         <thead><tr><th>Flag</th><th>Description</th></tr></thead>
 *         <tbody>
 *           <tr><td>(Space)</td><td>Same as for ‘o’</td></tr>
 *           <tr><td><code>+</code></td><td>Same as for ‘o’</td></tr>
 *           <tr><td><code>0</code></td><td>Same as for ‘o’</td></tr>
 *           <tr><td><code>-</code></td><td>Same as for ‘o’</td></tr>
 *           <tr><td><code>#</code></td><td>Prefix non-zero values with “0x”</td></tr>
 *         </tbody>
 *       </table>
 *     </dd>
 *     <dt>X</dt>
 *     <dd>
 *       <p>Same as ‘x’, except that it uses uppercase letters instead.</p>
 *     </dd>
 *     <dt>b</dt>
 *     <dd>
 *       <p>Outputs</p>
 *
 *       <pre><code>[left-padding][sign][base-prefix][prefix][zeroes/ones]
 *       [precision-filler]binary-digits[right-padding]</code></pre>
 *
 *       <p><em>Left-padding</em> and <em>right-padding</em> are the same as
 *       for the ‘o’ directive described above.  <em>Base-prefix</em> and
 *       <em>prefix</em> are the same as for the ‘x’ directive, except that
 *       <em>base-prefix</em> outputs “0b”.  <em>Zeroes/ones</em> is the same
 *       as <em>zeroes/fs</em> for the ‘x’ directive, except that it uses ones
 *       instead of sevens.  The same goes for <em>precision-filler</em>.</p>
 *
 *       <p><em>Binary-digits</em> consists of the digits in base 2 that
 *       represent the result of #to_int on the argument, using ‘0’ and ‘1’.  A
 *       negative value will be output as a two’s complement value.</p>
 *
 *       <table>
 *         <thead><tr><th>Flag</th><th>Description</th></tr></thead>
 *         <tbody>
 *           <tr><td>(Space)</td><td>Same as for ‘o’</td></tr>
 *           <tr><td><code>+</code></td><td>Same as for ‘o’</td></tr>
 *           <tr><td><code>0</code></td><td>Same as for ‘o’</td></tr>
 *           <tr><td><code>-</code></td><td>Same as for ‘o’</td></tr>
 *           <tr><td><code>#</code></td><td>Prefix non-zero values with “0b”</td></tr>
 *         </tbody>
 *       </table>
 *     </dd>
 *     <dt>B</dt>
 *     <dd>
 *       <p>Same as ‘b’, except that it uses a “0B” prefix for the
 *       ‘<code>#</code>’ flag.</p>
 *     </dd>
 *     <dt>f</dt>
 *     <dd>
 *       <p>Outputs</p>
 *
 *       <pre><code>[left-padding][prefix/sign][zeroes]
 *       integer-part[decimal-point][fractional-part][right-padding]</code></pre>
 *
 *       <p>If a width <em>w</em> has been specified and neither the
 *       ‘<code>-</code>’ nor the ‘<code>0</code>’ flag has been given,
 *       <em>left-padding</em> consists of enough spaces to make the whole
 *       field at least <em>w</em> cells wide, otherwise it’s empty.</p>
 *
 *       <p><em>Prefix/sign</em> is “-” if the argument is negative, “+” if the
 *       ‘<code>+</code>’ flag was given, and “ ” if the ‘<code> </code>’ flag
 *       was given, otherwise it’s empty.</p>
 *
 *       <p>If a width <em>w</em> has been specified and the ‘<code>0</code>’
 *       flag has been given and the ‘<code>-</code>’ flag has not been given,
 *       <em>zeroes</em> consists of enough zeroes to make the whole field
 *       at least <em>w</em> cells wide, otherwise it’s empty.</p>
 *
 *       <p><em>Integer-part</em> consists of the digits in base 10 that
 *       represent the integer part of the result of calling Float with the
 *       argument as its argument.</p>
 *
 *       <p><em>Decimal-point</em> is “.” if the precision isn’t 0 or if the
 *       ‘<code>#</code>’ flag has been given.</p>
 *
 *       <p><em>Fractional-part</em> consists of <em>p</em> digits in base 10
 *       that represent the fractional part of the result of calling Float with
 *       the argument as its argument, where <em>p</em> = precision, if one has
 *       been specified, <em>p</em> = 6 otherwise.</p>
 *
 *       <p>If a width <em>w</em> has been specified and the ‘<code>-</code>’
 *       flag has been given, <em>right-padding</em> consists of enough spaces
 *       to make the whole field at least <em>w</em> cells wide, otherwise it’s
 *       empty.</p>
 *
 *       <table>
 *         <thead><tr><th>Flag</th><th>Description</th></tr></thead>
 *         <tbody>
 *           <tr>
 *             <td>(Space)</td>
 *             <td>Add a “ ” prefix to non-negative numbers</td>
 *           </tr>
 *           <tr>
 *             <td><code>+</code></td>
 *             <td>Add a “+” sign to non-negative numbers; overrides the
 *             ‘<code> </code>’ flag</td>
 *           </tr>
 *           <tr>
 *             <td><code>0</code></td>
 *             <td>Use ‘0’ for any width padding; ignored when a precision has
 *             been specified</td>
 *           </tr>
 *           <tr>
 *             <td><code>-</code></td>
 *             <td>Left justify the output with ‘ ’ as padding; overrides the
 *             ‘<code>0</code>’ flag</td>
 *           </tr>
 *           <tr>
 *             <td>#</td>
 *             <td>Output a decimal point, even if no fractional part
 *             follows</td>
 *           </tr>
 *         </tbody>
 *       </table>
 *     </dd>
 *     <dt>e</dt>
 *     <dd>
 *       <p>Outputs</p>
 *
 *       <pre><code>[left-padding][prefix/sign][zeroes]
 *       digit[decimal-point][fractional-part]exponent[right-padding]</code></pre>
 *
 *       <p>If a width <em>w</em> has been specified and neither the
 *       ‘<code>-</code>’ nor the ‘<code>0</code>’ flag has been given,
 *       <em>left-padding</em> consists of enough spaces to make the whole
 *       field at least <em>w</em> + <em>e</em> cells wide, where <em>e</em> ≥
 *       4 is the width of the exponent, otherwise it’s empty.</p>
 *
 *       <p><em>Prefix/sign</em> is “-” if the argument is negative, “+” if the
 *       ‘<code>+</code>’ flag was given, and “ ” if the ‘<code> </code>’ flag
 *       was given, otherwise it’s empty.</p>
 *
 *       <p>If a width <em>w</em> has been specified and the ‘<code>0</code>’
 *       flag has been given and the ‘<code>-</code>’ flag has not been given,
 *       <em>zeroes</em> consists of enough zeroes to make the whole field
 *       <em>w</em> + <em>e</em> cells wide, where <em>e</em> ≥ 4 is the width
 *       of the exponent, otherwise it’s empty.</p>
 *
 *       <p><em>Digit</em> consists of one digit in base 10 that represent the
 *       most significant digit of the result of calling Float with the
 *       argument as its argument.</p>
 *
 *       <p><em>Decimal-point</em> is “.” if the precision isn’t 0 or if the
 *       ‘<code>#</code>’ flag has been given.</p>
 *
 *       <p><em>Fractional-part</em> consists of <em>p</em> digits in base 10
 *       that represent all but the most significant digit of the result of
 *       calling Float with the argument as its argument, where <em>p</em> =
 *       precision, if one has been specified, <em>p</em> = 6 otherwise.</p>
 *
 *       <p><em>Exponent</em> consists of “e” followed by the exponent in base
 *       10 required to turn the result of calling Float with the argument as
 *       its argument into a decimal fraction with one non-zero digit in the
 *       integer part.  If the exponent is 0, “+00” will be output.</p>
 *
 *       <p>If a width <em>w</em> has been specified and the ‘<code>-</code>’
 *       flag has been given, <em>right-padding</em> consists of enough spaces
 *       to make the whole field at least <em>w</em> + <em>e</em> cells wide,
 *       where <em>e</em> ≥ 4 is the width of the exponent, otherwise it’s
 *       empty.</p>
 *
 *       <table>
 *         <thead><tr><th>Flag</th><th>Description</th></tr></thead>
 *         <tbody>
 *           <tr>
 *             <td>(Space)</td>
 *             <td>Add a “ ” prefix to non-negative numbers</td>
 *           </tr>
 *           <tr>
 *             <td><code>+</code></td>
 *             <td>Add a “+” sign to non-negative numbers; overrides the
 *             ‘<code> </code>’ flag</td>
 *           </tr>
 *           <tr>
 *             <td><code>0</code></td>
 *             <td>Use ‘0’ for any width padding; ignored when a precision has
 *             been specified</td>
 *           </tr>
 *           <tr>
 *             <td><code>-</code></td>
 *             <td>Left justify the output with ‘ ’ as padding; overrides the
 *             ‘<code>0</code>’ flag</td>
 *           </tr>
 *           <tr>
 *             <td>#</td>
 *             <td>Output a decimal point, even if no fractional part
 *             follows</td>
 *           </tr>
 *         </tbody>
 *       </table>
 *     </dd>
 *     <dt>E</dt>
 *     <dd>
 *       <p>Same as ‘e’, except that it uses an uppercase ‘E’ for the exponent
 *       separator.</p>
 *     </dd>
 *     <dt>g</dt>
 *     <dd>
 *       <p>Same as ‘e’ if the exponent is less than -4 or if the exponent is
 *       greater than or equal to the precision, otherwise ‘f’ is used.  The
 *       precision defaults to 6 and a precision of 0 is treated as a precision
 *       of 1.  Trailing zeros are removed from the fractional part of the
 *       result.</p>
 *     </dd>
 *     <dt>G</dt>
 *     <dd>
 *       <p>Same as ‘g’, except that it uses an uppercase ‘E’ for the exponent
 *       separator.</p>
 *     </dd>
 *     <dt>a</dt>
 *     <dd>
 *       <p>Outputs</p>
 *
 *       <pre><code>[left-padding][prefix/sign][zeroes]
 *       digit[hexadecimal-point][fractional-part]exponent[right-padding]</code></pre>
 *
 *       <p>If a width <em>w</em> has been specified and neither the
 *       ‘<code>-</code>’ nor the ‘<code>0</code>’ flag has been given,
 *       <em>left-padding</em> consists of enough spaces to make the whole
 *       field at least <em>w</em> + <em>e</em> cells wide, where <em>e</em> ≥
 *       3 is the width of the exponent, otherwise it’s empty.</p>
 *
 *       <p><em>Prefix/sign</em> is “-” if the argument is negative, “+” if the
 *       ‘<code>+</code>’ flag was given, and “ ” if the ‘<code> </code>’ flag
 *       was given, otherwise it’s empty.</p>
 *
 *       <p>If a width <em>w</em> has been specified and the ‘<code>0</code>’
 *       flag has been given and the ‘<code>-</code>’ flag has not been given,
 *       <em>zeroes</em> consists of enough zeroes to make the whole field
 *       <em>w</em> + <em>e</em> cells wide, where <em>e</em> ≥ 3 is the width
 *       of the exponent, otherwise it’s empty.</p>
 *
 *       <p><em>Digit</em> consists of one digit in base 16 that represent the
 *       most significant digit of the result of calling Float with the
 *       argument as its argument, using ‘0’ through ‘9’ and ‘a’ through ‘f’.</p>
 *
 *       <p><em>Decimal-point</em> is “.” if the precision isn’t 0 or if the
 *       ‘<code>#</code>’ flag has been given.</p>
 *
 *       <p><em>Fractional-part</em> consists of <em>p</em> digits in base 16
 *       that represent all but the most significant digit of the result of
 *       calling Float with the argument as its argument, where <em>p</em> =
 *       precision, if one has been specified, <em>p</em> = <em>q</em>, where
 *       <em>q</em> is the number of digits required to represent the number
 *       exactly, otherwise.  Digits are output using ‘0’ through ‘9’ and ‘a’
 *       through ‘f’.</p>
 *
 *       <p><em>Exponent</em> consists of “p” followed by the exponent of 2 in
 *       base 10 required to turn the result of calling Float with the argument
 *       as its argument into a decimal fraction with one non-zero digit in the
 *       integer part.  If the exponent is 0, “+0” will be output.</p>
 *
 *       <p>If a width <em>w</em> has been specified and the ‘<code>-</code>’
 *       flag has been given, <em>right-padding</em> consists of enough spaces
 *       to make the whole field at least <em>w</em> + <em>e</em> cells
 *       wide, where <em>e</em> ≥ 3 is the width of the exponent, otherwise
 *       it’s empty.</p>
 *
 *       <table>
 *         <thead><tr><th>Flag</th><th>Description</th></tr></thead>
 *         <tbody>
 *           <tr>
 *             <td>(Space)</td>
 *             <td>Add a “ ” prefix to non-negative numbers</td>
 *           </tr>
 *           <tr>
 *             <td><code>+</code></td>
 *             <td>Add a “+” sign to non-negative numbers; overrides the
 *             ‘<code> </code>’ flag</td>
 *           </tr>
 *           <tr>
 *             <td><code>0</code></td>
 *             <td>Use ‘0’ for any width padding; ignored when a precision has
 *             been specified</td>
 *           </tr>
 *           <tr>
 *             <td><code>-</code></td>
 *             <td>Left justify the output with ‘ ’ as padding; overrides the
 *             ‘<code>0</code>’ flag</td>
 *           </tr>
 *           <tr>
 *             <td>#</td>
 *             <td>Output a decimal point, even if no fractional part
 *             follows</td>
 *           </tr>
 *         </tbody>
 *       </table>
 *     </dd>
 *     <dt>A</dt>
 *     <dd>
 *       <p>Same as ‘a’, except that it uses an uppercase letters instead.</p>
 *     </dd>
 *   </dl>
 *
 *   A warning is issued if the ‘`0`’ flag is given when the ‘`-`’ flag has
 *   also been given to the ‘d’, ‘i’, ‘u’, ‘o’, ‘x’, ‘X’, ‘b’, or ‘B’
 *   directives.
 *
 *   A warning is issued if the ‘`0`’ flag is given when a precision has been
 *   specified for the ‘d’, ‘i’, ‘u’, ‘o’, ‘x’, ‘X’, ‘b’, or ‘B’ directives.
 *
 *   A warning is issued if the ‘<code> </code>’ flag is given when the ‘`+`’
 *   flag has also been given to the ‘d’, ‘i’, ‘u’, ‘o’, ‘x’, ‘X’, ‘b’, or ‘B’
 *   directives.
 *
 *   A warning is issued if the ‘`0`’ flag is given when the ‘o’, ‘x’, ‘X’,
 *   ‘b’, or ‘B’ directives has been given a negative argument.
 *
 *   A warning is issued if the ‘`#`’ flag is given when the ‘o’ directive has
 *   been given a negative argument.
 *
 *   Any taint on the receiver and any taint on arguments to any ‘s’ and ‘p’
 *   directives is inherited by the result.
 *
 *   @raise [ArgumentError] If the receiver isn’t a valid format specification
 *   @raise [ArgumentError] If any flags are given to the ‘%’, ‘\n’, or ‘\0’
 *     directives
 *   @raise [ArgumentError] If an argument is given to the ‘%’, ‘\n’, or ‘\0’
 *     directives
 *   @raise [ArgumentError] If a width is specified for the ‘%’, ‘\n’, or ‘\0’
 *     directives
 *   @raise [ArgumentError] If a precision is specified for the ‘%’, ‘\n’, ‘\0’,
 *     or ‘c’ directives
 *   @raise [ArgumentError] If any of the flags ‘<code> </code>’, ‘`+`’, ’`0`’,
 *     or ‘`#`’ are given to the ‘c’, ‘s’, or ‘p’ directives
 *   @raise [ArgumentError] If the ‘`#`’ flag is given to the ‘d’, ‘i’, or ‘u’
 *     directives
 *   @raise [ArgumentError] If the argument to the ‘c’ directive doesn’t respond
 *     to #to_str or #to_int
 *   @return [U::String] */
VALUE
rb_u_string_format_m(VALUE self, VALUE argument)
{
        volatile VALUE tmp = rb_check_array_type(argument);

        if (!NIL_P(tmp))
                return rb_u_string_format(RARRAY_LENINT(tmp), RARRAY_PTR(tmp), self);

        return rb_u_string_format(1, &argument, self);
}
