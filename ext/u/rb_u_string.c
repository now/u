#include <ruby.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>
#include "u.h"
#include "private.h"
#include "rb_private.h"
#include "rb_u_string.h"

VALUE rb_cUString;

static void
rb_u_string_mark(const UString *string)
{
        rb_gc_mark(string->rb);
}

static void
rb_u_string_free(UString *string)
{
        free((char *)string->c);
        free(string);
}

static VALUE
rb_u_string_create(VALUE rb, const char *str, long length)
{
        UString *string = ALLOC(UString);

        string->rb = rb;
        string->c = str;
        string->length = length;

        return USTRING2RVAL(string);
}


static VALUE
rb_u_string_alloc(UNUSED(VALUE klass))
{
        return rb_u_string_create(Qnil, NULL, 0);
}

VALUE
rb_u_string_new(const char *str, long length)
{
        char *copy = ALLOC_N(char, length + 1);
        MEMCPY(copy, str, char, length);
        copy[length] = '\0';

        return rb_u_string_create(Qnil, copy, length);
}

VALUE
rb_u_string_new_own(const char *str, long length)
{
        return rb_u_string_create(Qnil, str, length);
}

VALUE
rb_u_string_new_rb(VALUE str)
{
        return rb_u_string_create(str, NULL, 0);
}

static VALUE
rb_u_string_initialize(int argc, VALUE *argv, VALUE self)
{
        UString *string = RVAL2USTRING(self);
        VALUE rb;

        rb_scan_args(argc, argv, "01", &rb);
        if (!NIL_P(rb)) {
                StringValue(rb);
                string->rb = rb_str_freeze(rb);
        }

        return Qnil;
}

static VALUE
rb_u_string_initialize_copy(VALUE self, VALUE rboriginal)
{
        UString *string = RVAL2USTRING(self);
        const UString *original = RVAL2USTRING(rboriginal);

        if (string == original)
                return self;

        string->rb = original->rb;
        string->c = original->c;
        string->length = original->length;

        return self;
}

VALUE
rb_u_string_dup(VALUE self)
{
        const UString *string = RVAL2USTRING(self);

        return rb_u_string_create(string->rb, string->c, string->length);
}

static const char *
rb_u_string_begin_setup(VALUE self, long offset, const char **base_limit, const char **limit)
{
        const UString *string = RVAL2USTRING(self);
        const char *base = USTRING_STR(string);

        *base_limit = base + USTRING_LENGTH(string);
        *limit = *base_limit;

        if (offset < 0) {
                const char *tmp = base;
                base = *base_limit;
                *base_limit = tmp;
        }

        return base;
}

/* TODO: instead of ‘end’, perhaps use a len/max-type parameter? */
static char *
_utf_offset_to_pointer_validated_impl(const char *str, long offset,
                                      const char *limit, bool noisy)
{
	const char *p = str;
        long saved_offset = offset;

        if (offset > 0) {
                while (p < limit && offset-- > 0)
                        p = u_next(p);

                if (offset > 0) {
                        if (noisy)
                                rb_raise(rb_eIndexError,
                                         "index %ld lays beyond end of string",
                                         saved_offset);
                        else
                                return NULL;
                }
        } else {
                while (offset != 0) {
                        const char *base = p;
                        p += offset;
                        while (p >= limit && (*p & 0xc0) == 0x80)
                                p--;

                        if (p < limit) {
                                if (noisy)
                                        rb_raise(rb_eIndexError,
                                                "index %ld lays before beginning of string",
                                                saved_offset);
                                else
                                        return NULL;
                        }

                        offset += u_pointer_to_offset(p, base);
                 }
        }

	return (char *)p;
}

static char *
_utf_offset_to_pointer_validated(const char *str, long offset, const char *end)
{
        return _utf_offset_to_pointer_validated_impl(str, offset, end, true);
}

static char *
_utf_offset_to_pointer_failable(const char *str, long offset, const char *end)
{
        return _utf_offset_to_pointer_validated_impl(str, offset, end, false);
}

bool
rb_u_string_begin_from_offset(VALUE self, long offset,
                              const char **begin, const char **limit)
{
        const char *base_limit;
        const char *base = rb_u_string_begin_setup(self, offset, &base_limit, limit);

        *begin = _utf_offset_to_pointer_failable(base, offset, base_limit);

        return (*begin != NULL);
}

void
rb_u_string_begin_from_offset_validated(VALUE self, long offset,
                                        const char **begin, const char **limit)
{
        const char *base_limit;
        const char *base = rb_u_string_begin_setup(self, offset, &base_limit, limit);

        *begin = _utf_offset_to_pointer_validated(base, offset, base_limit);
}

void
Init_u_string(VALUE mU)
{
        rb_cUString = rb_define_class_under(mU, "String", rb_cData);

        rb_include_module(rb_cUString, rb_mComparable);

        rb_define_alloc_func(rb_cUString, rb_u_string_alloc);
        rb_define_private_method(rb_cUString, "initialize", rb_u_string_initialize, -1);
        rb_define_private_method(rb_cUString, "initialize_copy", rb_u_string_initialize_copy, 1);
        rb_define_method(rb_cUString, "<=>", rb_u_string_collate, 1);
        rb_define_method(rb_cUString, "==", rb_u_string_equal, 1);
        rb_define_method(rb_cUString, "===", rb_u_string_equal, 1);
        rb_define_method(rb_cUString, "eql?", rb_u_string_eql, 1);
        rb_define_method(rb_cUString, "casecmp", rb_u_string_casecmp, 1);
        rb_define_method(rb_cUString, "center", rb_u_string_center, -1);
        rb_define_method(rb_cUString, "chars", rb_u_string_each_char, 0);
        rb_define_method(rb_cUString, "[]", rb_u_string_aref_m, -1);
        rb_define_method(rb_cUString, "chomp", rb_u_string_chomp, -1);
        rb_define_method(rb_cUString, "chop", rb_u_string_chop, 0);
        rb_define_method(rb_cUString, "count", rb_u_string_count, -1);
        rb_define_method(rb_cUString, "delete", rb_u_string_delete, -1);
        rb_define_method(rb_cUString, "downcase", rb_u_string_downcase, 0);
        rb_define_method(rb_cUString, "each_char", rb_u_string_each_char, 0);
        rb_define_method(rb_cUString, "foldcase", rb_u_string_foldcase, 0);
        rb_define_method(rb_cUString, "hex", rb_u_string_hex, 0);
        rb_define_method(rb_cUString, "index", rb_u_string_index_m, -1);
        rb_define_method(rb_cUString, "inspect", rb_u_string_inspect, 0);
        rb_define_method(rb_cUString, "length", rb_u_string_length, 0);
        rb_define_method(rb_cUString, "ljust", rb_u_string_ljust, -1);
        rb_define_method(rb_cUString, "lstrip", rb_u_string_lstrip, 0);
        rb_define_method(rb_cUString, "normalize", rb_u_string_normalize, -1);
        rb_define_method(rb_cUString, "oct", rb_u_string_oct, 0);
        rb_define_method(rb_cUString, "reverse", rb_u_string_reverse, 0);
        rb_define_method(rb_cUString, "rindex", rb_u_string_rindex_m, -1);
        rb_define_method(rb_cUString, "rjust", rb_u_string_rjust, -1);
        rb_define_method(rb_cUString, "rstrip", rb_u_string_rstrip, 0);
        rb_define_method(rb_cUString, "squeeze", rb_u_string_squeeze, -1);
        rb_define_method(rb_cUString, "strip", rb_u_string_strip, 0);
        rb_define_method(rb_cUString, "to_i", rb_u_string_to_i, -1);
        rb_define_method(rb_cUString, "to_s", rb_u_string_to_str, 0);
        rb_define_method(rb_cUString, "to_str", rb_u_string_to_str, 0);
        rb_define_method(rb_cUString, "tr", rb_u_string_tr, 2);
        rb_define_method(rb_cUString, "tr_s", rb_u_string_tr_s, 2);
        rb_define_method(rb_cUString, "upcase", rb_u_string_upcase, 0);
}
