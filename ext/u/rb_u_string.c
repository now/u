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
        VALUE result = rb_u_string_create(str, NULL, 0);

        OBJ_INFECT(result, str);

        return result;
}

VALUE
rb_u_string_new_subsequence(VALUE self, long begin, long length)
{
        const UString *string = RVAL2USTRING(self);

        /* TODO: Create a subsequence of self, starting at begin and running
         * through length bytes.  The returned value should be infected. */
        VALUE result = rb_u_string_new(USTRING_STR(string) + begin, length);

        OBJ_INFECT(result, self);

        return result;
}

VALUE
rb_u_string_new_empty(VALUE self)
{
        return rb_u_string_new_subsequence(self, 0, 0);
}

VALUE
rb_u_string_check_type(VALUE str)
{
        if (rb_obj_is_kind_of(str, rb_cUString))
                return str;

        return rb_check_string_type(str);
}

VALUE
rb_u_string_validate_type(VALUE str)
{
        VALUE converted = rb_u_string_check_type(str);

        if (NIL_P(converted))
                rb_raise(rb_eTypeError, "type mismatch: %s given",
                         rb_obj_classname(str));

        return converted;
}

VALUE
rb_u_string_object_as_string(VALUE object)
{
        if (TYPE(object) == T_STRING || rb_obj_is_kind_of(object, rb_cUString))
                return object;

        static ID id_to_s;
        if (id_to_s == 0)
                id_to_s = rb_intern("to_s");

        VALUE str = rb_funcall(object, id_to_s, 0);
        if (TYPE(str) != T_STRING)
                return rb_any_to_s(object);

        if (OBJ_TAINTED(object))
                OBJ_TAINT(str);

        return str;
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
                OBJ_INFECT(self, string->rb);
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

        OBJ_INFECT(self, rboriginal);

        return self;
}

VALUE
rb_u_string_dup(VALUE self)
{
        const UString *string = RVAL2USTRING(self);

        return rb_u_string_create(string->rb, string->c, string->length);
}

void
Init_u_string(VALUE mU)
{
        rb_cUString = rb_define_class_under(mU, "String", rb_cData);

        rb_include_module(rb_cUString, rb_mComparable);

        rb_define_alloc_func(rb_cUString, rb_u_string_alloc);
        rb_define_private_method(rb_cUString, "initialize", rb_u_string_initialize, -1);
        rb_define_private_method(rb_cUString, "initialize_copy", rb_u_string_initialize_copy, 1);
        rb_define_method(rb_cUString, "%", rb_u_string_format_m, 1);
        rb_define_method(rb_cUString, "*", rb_u_string_times, 1);
        rb_define_method(rb_cUString, "+", rb_u_string_plus, 1);
        rb_define_method(rb_cUString, "<=>", rb_u_string_collate, 1);
        rb_define_method(rb_cUString, "==", rb_u_string_equal, 1);
        rb_define_method(rb_cUString, "===", rb_u_string_equal, 1);
        rb_define_method(rb_cUString, "=~", rb_u_string_match, 1);
        rb_define_method(rb_cUString, "eql?", rb_u_string_eql, 1);
        rb_define_method(rb_cUString, "ascii_only?", rb_u_string_ascii_only, 0);
        rb_define_method(rb_cUString, "bytes", rb_u_string_each_byte, 0);
        rb_define_method(rb_cUString, "bytesize", rb_u_string_bytesize, 0);
        rb_define_method(rb_cUString, "casecmp", rb_u_string_casecmp, 1);
        rb_define_method(rb_cUString, "center", rb_u_string_center, -1);
        rb_define_method(rb_cUString, "chars", rb_u_string_each_char, 0);
        rb_define_method(rb_cUString, "[]", rb_u_string_aref_m, -1);
        rb_define_method(rb_cUString, "chomp", rb_u_string_chomp, -1);
        rb_define_method(rb_cUString, "chop", rb_u_string_chop, 0);
        rb_define_method(rb_cUString, "chr", rb_u_string_chr, 0);
        rb_define_method(rb_cUString, "codepoints", rb_u_string_each_codepoint, 0);
        rb_define_method(rb_cUString, "count", rb_u_string_count, -1);
        rb_define_method(rb_cUString, "delete", rb_u_string_delete, -1);
        rb_define_method(rb_cUString, "downcase", rb_u_string_downcase, 0);
        rb_define_method(rb_cUString, "each", rb_u_string_each_line, -1);
        rb_define_method(rb_cUString, "each_byte", rb_u_string_each_byte, 0);
        rb_define_method(rb_cUString, "each_char", rb_u_string_each_char, 0);
        rb_define_method(rb_cUString, "each_codepoint", rb_u_string_each_codepoint, 0);
        rb_define_method(rb_cUString, "each_line", rb_u_string_each_line, -1);
        rb_define_method(rb_cUString, "empty?", rb_u_string_empty, 0);
        rb_define_method(rb_cUString, "end_with?", rb_u_string_ends_with, -1);
        rb_define_method(rb_cUString, "ends_with?", rb_u_string_ends_with, -1);
        rb_define_method(rb_cUString, "foldcase", rb_u_string_foldcase, 0);
        rb_define_method(rb_cUString, "format", rb_u_string_format_m, 1);
        rb_define_method(rb_cUString, "gsub", rb_u_string_gsub, -1);
        rb_define_method(rb_cUString, "hash", rb_u_string_hash, 0);
        rb_define_method(rb_cUString, "hex", rb_u_string_hex, 0);
        rb_define_method(rb_cUString, "include?", rb_u_string_include, 1);
        rb_define_method(rb_cUString, "index", rb_u_string_index_m, -1);
        rb_define_method(rb_cUString, "inspect", rb_u_string_inspect, 0);
        rb_define_method(rb_cUString, "intern", rb_u_string_to_sym, 0);
        rb_define_method(rb_cUString, "length", rb_u_string_length, 0);
        rb_define_method(rb_cUString, "lines", rb_u_string_each_line, -1);
        rb_define_method(rb_cUString, "ljust", rb_u_string_ljust, -1);
        rb_define_method(rb_cUString, "lstrip", rb_u_string_lstrip, 0);
        rb_define_method(rb_cUString, "normalize", rb_u_string_normalize, -1);
        rb_define_method(rb_cUString, "oct", rb_u_string_oct, 0);
        rb_define_method(rb_cUString, "partition", rb_u_string_partition, 1);
        rb_define_method(rb_cUString, "reverse", rb_u_string_reverse, 0);
        rb_define_method(rb_cUString, "rindex", rb_u_string_rindex_m, -1);
        rb_define_method(rb_cUString, "rjust", rb_u_string_rjust, -1);
        rb_define_method(rb_cUString, "rpartition", rb_u_string_rpartition, 1);
        rb_define_method(rb_cUString, "rstrip", rb_u_string_rstrip, 0);
        rb_define_method(rb_cUString, "scan", rb_u_string_scan, 1);
        rb_define_method(rb_cUString, "split", rb_u_string_split_m, -1);
        rb_define_method(rb_cUString, "squeeze", rb_u_string_squeeze, -1);
        rb_define_method(rb_cUString, "strip", rb_u_string_strip, 0);
        rb_define_method(rb_cUString, "to_i", rb_u_string_to_i, -1);
        rb_define_method(rb_cUString, "to_s", rb_u_string_to_str, 0);
        rb_define_method(rb_cUString, "to_str", rb_u_string_to_str, 0);
        rb_define_method(rb_cUString, "to_sym", rb_u_string_to_sym, 0);
        rb_define_method(rb_cUString, "tr", rb_u_string_tr, 2);
        rb_define_method(rb_cUString, "tr_s", rb_u_string_tr_s, 2);
        rb_define_method(rb_cUString, "upcase", rb_u_string_upcase, 0);
        rb_define_method(rb_cUString, "valid_encoding?", rb_u_string_valid_encoding, 0);
}
