#ifndef RB_U_STRING_H
#define RB_U_STRING_H


/* TODO: Move this to rb_u_string.c and turn USTRING_STR() into
 * rb_u_string_c_str() and USTRING_LENGTH() into rb_u_string_c_length() */
struct rb_u_string {
        VALUE rb;
        const char *c;
        long length;
};


#define RVAL2USTRING(object) \
        (Check_Type(object, T_DATA), (struct rb_u_string *)DATA_PTR(object))

#define RVAL2USTRING_ANY(value) \
        (rb_obj_is_kind_of((value), rb_cUString) ? \
         RVAL2USTRING(value) : \
         USTRING_LOCAL(StringValue(value), NULL, 0))

#define USTRING2RVAL(string) \
        Data_Wrap_Struct(rb_cUString, rb_u_string_mark, rb_u_string_free, string)

#define USTRING_LOCAL(arb, ac, alength) \
        (&(struct rb_u_string){ .rb = (arb), .c = (ac), .length = (alength) })

/* TODO: Call this USTRING_BEGIN() instead */
#define USTRING_STR(string) \
        (NIL_P((string)->rb) ? (string)->c : RSTRING_PTR(string->rb))

#define USTRING_LENGTH(string) \
        (NIL_P((string)->rb) ? (string)->length : RSTRING_LEN(string->rb))

#define USTRING_END(string) \
        (NIL_P((string)->rb) ? (string)->c + (string)->length : RSTRING_END(string->rb))

static inline const char *
rb_u_string_begin_from_offset(const struct rb_u_string *string, long offset)
{
        return u_offset_to_pointer_n(offset >= 0 ?
                                        USTRING_STR(string) :
                                        USTRING_END(string),
                                     offset,
                                     USTRING_LENGTH(string));
}


extern VALUE rb_cUString;


VALUE rb_u_string_new_uninfected(const char *str, long length);
VALUE rb_u_string_new_uninfected_own(const char *str, long length);
VALUE rb_u_string_new_c(VALUE self, const char *str, long length);
VALUE rb_u_string_new_c_own(VALUE self, const char *str, long length);
VALUE rb_u_string_new_rb(VALUE str);
VALUE rb_u_string_new_subsequence(VALUE self, long begin, long length);
VALUE rb_u_string_new_empty(VALUE self);

VALUE rb_u_string_check_type(VALUE str);
VALUE rb_u_string_validate_type(VALUE str);
VALUE rb_u_string_object_as_string(VALUE object);

const char *rb_u_string_begin_from_offset(const struct rb_u_string *string, long offset);

/* TODO: Rename sub. */
/* TODO: Move to rb_private.h. */
long rb_u_string_index(VALUE self, VALUE sub, long offset);
long rb_u_string_rindex(VALUE self, VALUE rbsubstring, long offset);

VALUE rb_u_string_alnum(VALUE self);
VALUE rb_u_string_alpha(VALUE self);
VALUE rb_u_string_assigned(VALUE self);
VALUE rb_u_string_aref_m(int argc, VALUE *argv, VALUE self);
VALUE rb_u_string_ascii_only(VALUE self);
VALUE rb_u_string_b(VALUE self);
VALUE rb_u_string_bytesize(VALUE self);
VALUE rb_u_string_byteslice_m(int argc, VALUE *argv, VALUE self);
VALUE rb_u_string_center(int argc, VALUE *argv, VALUE self);
VALUE rb_u_string_casecmp(VALUE self, VALUE other);
VALUE rb_u_string_cased(VALUE self);
VALUE rb_u_string_case_ignorable(VALUE self);
VALUE rb_u_string_chomp(int argc, VALUE *argv, VALUE self);
VALUE rb_u_string_chop(VALUE self);
VALUE rb_u_string_chr(VALUE self);
VALUE rb_u_string_cntrl(VALUE self);
VALUE rb_u_string_collate(VALUE self, VALUE other);
VALUE rb_u_string_collate_key(VALUE self);
VALUE rb_u_string_combining_class(VALUE self);
VALUE rb_u_string_count(int argc, VALUE *argv, VALUE self);
VALUE rb_u_string_defined(VALUE self);
VALUE rb_u_string_delete(int argc, VALUE *argv, VALUE self);
VALUE rb_u_string_digit(VALUE self);
VALUE rb_u_string_downcase(int argc, VALUE *argv, VALUE self);
VALUE rb_u_string_dump(VALUE self);
VALUE rb_u_string_dup(VALUE self);
VALUE rb_u_string_each_byte(VALUE self);
VALUE rb_u_string_each_char(VALUE self);
VALUE rb_u_string_each_codepoint(VALUE self);
VALUE rb_u_string_each_grapheme_cluster(VALUE self);
VALUE rb_u_string_each_line(int argc, VALUE *argv, VALUE self);
VALUE rb_u_string_each_word(VALUE self);
VALUE rb_u_string_empty(VALUE self);
VALUE rb_u_string_end_with(int argc, VALUE *argv, VALUE self);
VALUE rb_u_string_equal(VALUE self, VALUE other);
VALUE rb_u_string_eql(VALUE self, VALUE other);
VALUE rb_u_string_foldcase(VALUE self);
VALUE rb_u_string_folded(VALUE self);
VALUE rb_u_string_format(int argc, const VALUE *argv, VALUE self);
VALUE rb_u_string_format_m(VALUE self, VALUE argument);
VALUE rb_u_string_general_category(VALUE self);
VALUE rb_u_string_getbyte(VALUE self, VALUE rbindex);
VALUE rb_u_string_graph(VALUE self);
VALUE rb_u_string_grapheme_break(VALUE self);
VALUE rb_u_string_gsub(int argc, VALUE *argv, VALUE self);
VALUE rb_u_string_hash(VALUE self);
VALUE rb_u_string_hex(VALUE self);
VALUE rb_u_string_index_m(int argc, VALUE *argv, VALUE self);
VALUE rb_u_string_include(VALUE self, VALUE other);
VALUE rb_u_string_inspect(VALUE self);
VALUE rb_u_string_length(VALUE self);
VALUE rb_u_string_line_break(VALUE self);
VALUE rb_u_string_ljust(int argc, VALUE *argv, VALUE self);
VALUE rb_u_string_lower(int argc, VALUE *argv, VALUE self);
VALUE rb_u_string_lstrip(VALUE self);
VALUE rb_u_string_match(VALUE self, VALUE other);
VALUE rb_u_string_match_m(int argc, VALUE *argv, VALUE self);
VALUE rb_u_string_mirror(VALUE self);
VALUE rb_u_string_normalize(int argc, VALUE *argv, VALUE self);
VALUE rb_u_string_newline(VALUE self);
VALUE rb_u_string_oct(VALUE self);
VALUE rb_u_string_ord(VALUE self);
VALUE rb_u_string_partition(VALUE self, VALUE separator);
VALUE rb_u_string_plus(VALUE self, VALUE rbother);
VALUE rb_u_string_print(VALUE self);
VALUE rb_u_string_punct(VALUE self);
VALUE rb_u_string_reverse(VALUE self);
VALUE rb_u_string_rindex_m(int argc, VALUE *argv, VALUE self);
VALUE rb_u_string_rjust(int argc, VALUE *argv, VALUE self);
VALUE rb_u_string_rpartition(VALUE self, VALUE separator);
VALUE rb_u_string_rstrip(VALUE self);
VALUE rb_u_string_scan(VALUE self, VALUE pattern);
VALUE rb_u_string_script(VALUE self);
VALUE rb_u_string_soft_dotted(VALUE self);
VALUE rb_u_string_space(VALUE self);
VALUE rb_u_string_split(VALUE self, const char *separator, long length);
VALUE rb_u_string_split_m(int argc, VALUE *argv, VALUE self);
VALUE rb_u_string_squeeze(int argc, VALUE *argv, VALUE self);
VALUE rb_u_string_start_with(int argc, VALUE *argv, VALUE self);
VALUE rb_u_string_strip(VALUE self);
VALUE rb_u_string_sub(int argc, VALUE *argv, VALUE self);
VALUE rb_u_string_substr(VALUE self, long offset, long len);
VALUE rb_u_string_times(VALUE self, VALUE rbtimes);
VALUE rb_u_string_title(VALUE self);
VALUE rb_u_string_titlecase(int argc, VALUE *argv, VALUE self);
VALUE rb_u_string_to_i(int argc, VALUE *argv, VALUE self);
VALUE rb_u_string_to_str(VALUE self);
VALUE rb_u_string_to_sym(VALUE self);
VALUE rb_u_string_tr(VALUE self, VALUE from, VALUE to);
VALUE rb_u_string_tr_s(VALUE self, VALUE from, VALUE to);
VALUE rb_u_string_upcase(int argc, VALUE *argv, VALUE self);
VALUE rb_u_string_upper(int argc, VALUE *argv, VALUE self);
VALUE rb_u_string_valid(VALUE self);
VALUE rb_u_string_valid_encoding(VALUE self);
VALUE rb_u_string_wide(VALUE self);
VALUE rb_u_string_wide_cjk(VALUE self);
VALUE rb_u_string_width(VALUE self);
VALUE rb_u_string_word_break(VALUE self);
VALUE rb_u_string_xdigit(VALUE self);
VALUE rb_u_string_zero_width(VALUE self);


void Init_u_string(VALUE mU);


#endif
