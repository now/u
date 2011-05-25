#include "rb_includes.h"
#include <limits.h>
#include <math.h>
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

#ifndef HAVE_RB_LONG2INT
static void
rb_out_of_int(long l)
{
        rb_raise(rb_eRangeError,
                 l < 0 ?
                        "integer %ld too small to convert to C type int" :
                        "integer %ld too big to convert to C type int",
                 l);
}
#  if defined(__GNUC__) && __GNUC__ > 2
#    define rb_long2int(l) __extension__({ \
        long _rb_long2int_l = (l); \
        int _rb_long2int_i = (int)_rb_long2int_l; \
        if ((long)_rb_long2int_i != _rb_long2int_l) \
                rb_out_of_int(_rb_long2int_l); \
        _rb_long2int_i; \
})
#  else
static inline int
rb_long2int(long l)
{
        int i = (int)l;

        if ((long)i != l)
                rb_out_of_int(l);

        return i;
}
#endif
#else
#  define rb_long2int(l) ((int)(l))
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

        if (*p == end)
                rb_raise(rb_eArgError, "directive missing after %s", type);

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
#if defined(HAVE_RB_INTERN3) && defined(HAVE_RB_UTF8_ENCODING)
        *argument_id = rb_intern3(base, length, rb_utf8_encoding());
#else
        char name[length + 1];
        memcpy(name, base, length);
        name[length] = '\0';
        *argument_id = rb_intern(name);
#endif

        *p = rb_u_next_validated(q, end);

        if (*p == end)
                rb_raise(rb_eArgError, "directive missing after argument name");
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

                if (flags & flag)
                        rb_warning("repeated flag in format: ‘%c’", c);
                flags |= flag;

                *p = u_next(*p);
        }

        if (flags != DIRECTIVE_FLAGS_NONE && *p == end)
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
        if (*p == end)
                return 0;

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
        if (*p == end)
                return -1;

        unichar c = _rb_u_aref_char_validated(*p, end);

        if (c != '.')
                return -1;

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
        if (precision >= 0)
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
                if (rb_obj_is_kind_of(argument, rb_cUString))
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
                        const char *prefix, unichar precision_filler, const char *digits, int length,
                        VALUE result)
{
        int prefix_length = strlen(prefix);
        width -= prefix_length;

        if (precision >= 0)
                flags &= ~DIRECTIVE_FLAGS_ZERO;

        if (precision < length)
                precision = length;
        width -= precision;

        if (!(flags & DIRECTIVE_FLAGS_MINUS) && !(flags & DIRECTIVE_FLAGS_ZERO))
                rb_u_buffer_append_unichar_n(result, ' ', width);

        rb_u_buffer_append(result, prefix, prefix_length);

        if (!(flags & DIRECTIVE_FLAGS_MINUS) && (flags & DIRECTIVE_FLAGS_ZERO))
                rb_u_buffer_append_unichar_n(result, '0', width);

        rb_u_buffer_append_unichar_n(result, precision_filler, precision - length);

        rb_u_buffer_append(result, digits, length);

        if (flags & DIRECTIVE_FLAGS_MINUS)
                rb_u_buffer_append_unichar_n(result, ' ', width);
}

#define BITS2DECIMALDIGITS(n) (((long)(n) * 146) / 485 + 1) /* log2(10) ≈ 146/485 */
#define BITS2OCTALDIGITS(n) ((long)(n) * 3 + 1) /* log2(8) = 3 */

#define DIGITS_BUFFER_SIZE (BITS2OCTALDIGITS(sizeof(long) * CHAR_BIT) + 1)

#define BASE2FORMAT(base) \
        ((base) == 10 ? "%ld" : ((base) == 16 ? "%lx" : "%lo"))

static bool
directive_number_sign(unichar directive, bool negative, int flags, char *sign)
{
        if (flags & DIRECTIVE_FLAGS_PLUS && flags & DIRECTIVE_FLAGS_SPACE)
                rb_warning("‘%lc’ directive ignores ‘ ’ flag when ‘+’ flag has been specified",
                           directive);

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
directive_number_long_signed(unichar directive, int flags, long argument,
                             int base, char *sign, const char **digits, char *buffer)
{
        if (directive_number_sign(directive, argument < 0, flags, sign))
                argument = -argument;

        *digits = buffer;
        return snprintf(buffer, DIGITS_BUFFER_SIZE, BASE2FORMAT(base), argument);
}

static inline int
directive_number_bignum_signed(unichar directive, int flags, VALUE argument,
                               int base, char *sign, const char **digits, VALUE *str)
{
        *str = rb_big2str(argument, base);
        *digits = RSTRING_PTR(*str);
        if (directive_number_sign(directive, *digits[0] == '-', flags, sign))
                (*digits)++;

        /* TODO: Why aren’t we passing around width and precision as longs? */
        return rb_long2int(RSTRING_END(*str) - *digits);
}

static void
directive_number_check_flags(unichar directive, int flags, int precision)
{
        if ((flags & DIRECTIVE_FLAGS_MINUS) && (flags & DIRECTIVE_FLAGS_ZERO))
                rb_warning("‘%lc’ directive ignores ‘0’ flag when ‘-’ flag has been specified",
                           directive);

        if (precision >= 0 && (flags & DIRECTIVE_FLAGS_ZERO))
                rb_warning("‘%lc’ directive ignores ‘0’ flag when precision (%d) has been specified",
                           directive, precision);
}

static int
directive_signed_number(unichar directive, int flags, int precision, VALUE argument,
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
                length -= *digits - buffer;
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
directive_unsigned_number(unichar directive, int flags, int precision, VALUE argument,
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
directive_signed_or_unsigned_number(unichar directive, int flags, int precision, VALUE argument,
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
directive_integer(unichar directive, int flags, int width, int precision, VALUE argument, VALUE result)
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
directive_unsigned_number_output(unichar directive, int flags, int width, int precision,
                                 char *prefix, const char *digits, int length,
                                 VALUE result)
{
        if (directive_number_is_unsigned(prefix)) {
                if (flags & DIRECTIVE_FLAGS_ZERO)
                        rb_warning("‘%lc’ directive ignores ‘0’ flag when given a negative argument",
                                   directive);

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
directive_octal(unichar directive, int flags, int width, int precision, VALUE argument, VALUE result)
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
                        rb_warning("‘%lc’ directive ignores ‘#’ flag when given a negative argument",
                                   directive);

                for (char *p = prefix; *p != '\0'; p++)
                        *p = *(p + 1);
        }

        directive_unsigned_number_output(directive, flags, width, precision, prefix, digits, length, result);
}

static void
directive_hexadecimal(unichar directive, int flags, int width, int precision, VALUE argument, VALUE result)
{
        char prefix[] = "0x\0\0\0\0";
        if (directive == 'X')
                prefix[1] = 'X';
        char buffer[DIGITS_BUFFER_SIZE];
        VALUE str;
        const char *digits;
        int length = directive_signed_or_unsigned_number(directive, flags, precision, argument, 16, prefix, &digits, buffer, &str);

        if (directive == 'X')
                for (char *p = (char *)digits; *p != '\0'; p++)
                        *p = unichar_toupper(*p);

        directive_unsigned_number_output(directive, flags, width, precision, prefix, digits, length, result);
}

static void
directive_binary(unichar directive, int flags, int width, int precision, VALUE argument, VALUE result)
{
        char prefix[] = "0b\0\0\0\0";
        if (directive == 'B')
                prefix[1] = 'B';
        char buffer[DIGITS_BUFFER_SIZE];
        VALUE str;
        const char *digits;
        int length = directive_signed_or_unsigned_number(directive, flags, precision, argument, 2, prefix, &digits, buffer, &str);

        directive_unsigned_number_output(directive, flags, width, precision, prefix, digits, length, result);
}

static inline void
directive_float_nan(unichar directive, int flags, int width, VALUE result)
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
directive_float_inf(unichar directive, int flags, int width, double argument, VALUE result)
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
directive_float_format(unichar directive, int flags, int width, int precision, double argument, VALUE result)
{
        /* % + flags{0,4} + width_digits? + (. + precision_digits)? + \0 */
        char format[1 +
                    4 +
                    BITS2DECIMALDIGITS(sizeof(width) * CHAR_BIT) +
                    1 +
                    BITS2DECIMALDIGITS(sizeof(precision) * CHAR_BIT) +
                    1];
        char *p = format;
        const char *end = format + sizeof(format);

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
        int needed = 1 +
                2 +
                1 +
                abs(BITS2DECIMALDIGITS(exponent)) +
                1 +
                (precision >= 0 ? precision : 0) +
                1 +
                1;
        if (needed < width)
                needed = width;
        needed += 1;
        char buffer[needed];
        int length = snprintf(buffer, needed, format, argument);
        if (length > needed)
                rb_raise(rb_eRuntimeError,
                         "buffer calculation size is wrong: %d < %d",
                         needed, length);

        rb_u_buffer_append(result, buffer, length);
}
#pragma GCC diagnostic warning "-Wformat-nonliteral"

static void
directive_float(unichar directive, int flags, int width, int precision, VALUE argument, VALUE result)
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
        /* TODO: Use DirectiveFlags instead of int. */
        int flags = directive_flags(p, end, arguments, &argument, &argument_to_s);
        if (argument_to_s) {
                directive_validate_flags('s', flags, DIRECTIVE_FLAGS_MINUS);
                directive_string('s', flags, 0, 0, argument, result);
                return;
        }

        int width = directive_width(p, end, arguments, &flags);

        int precision = directive_precision(p, end);

        unichar c = '\0';
        if (*p < end) {
                c = _rb_u_aref_char_validated(*p, end);
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
                { 'u', DIRECTIVE_FLAGS_NUMBER, true, true, directive_integer },
                { 'o', DIRECTIVE_FLAGS_DECIMAL, true, true, directive_octal },
                { 'x', DIRECTIVE_FLAGS_DECIMAL, true, true, directive_hexadecimal },
                { 'X', DIRECTIVE_FLAGS_DECIMAL, true, true, directive_hexadecimal },
                { 'b', DIRECTIVE_FLAGS_DECIMAL, true, true, directive_binary },
                { 'B', DIRECTIVE_FLAGS_DECIMAL, true, true, directive_binary },
                { 'f', DIRECTIVE_FLAGS_DECIMAL, true, true, directive_float },
                { 'g', DIRECTIVE_FLAGS_DECIMAL, true, true, directive_float },
                { 'G', DIRECTIVE_FLAGS_DECIMAL, true, true, directive_float },
                { 'e', DIRECTIVE_FLAGS_DECIMAL, true, true, directive_float },
                { 'E', DIRECTIVE_FLAGS_DECIMAL, true, true, directive_float },
                { 'a', DIRECTIVE_FLAGS_DECIMAL, true, true, directive_float },
                { 'A', DIRECTIVE_FLAGS_DECIMAL, true, true, directive_float }
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
rb_u_buffer_append_format(int argc, const VALUE *argv, VALUE self, VALUE format)
{
        const UString *string = RVAL2USTRING_ANY(format);
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

        return self;
}

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
