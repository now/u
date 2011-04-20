#ifndef RB_U_STRING_H
#define RB_U_STRING_H


typedef struct _UString UString;

/* TODO: Move this to rb_u_string.c and turn USTRING_STR() into
 * rb_u_string_c_str() and USTRING_LENGTH() into rb_u_string_c_length() */
struct _UString {
        VALUE rb;
        const char *c;
        long length;
};


#define RVAL2USTRING(object) \
        (Check_Type(object, T_DATA), (UString *)DATA_PTR(object))

#define RVAL2USTRING_ANY(value) \
        (rb_obj_is_kind_of((value), rb_cUString) ? \
         RVAL2USTRING(value) : \
         USTRING_LOCAL(StringValue(value), NULL, 0))

#define USTRING2RVAL(string) \
        Data_Wrap_Struct(rb_cUString, rb_u_string_mark, rb_u_string_free, string)

#define USTRING_LOCAL(arb, ac, alength) \
        (&(UString){ .rb = (arb), .c = (ac), .length = (alength) })

/* TODO: Call this USTRING_BEGIN() instead */
#define USTRING_STR(string) \
        (NIL_P((string)->rb) ? (string)->c : RSTRING_PTR(string->rb))

#define USTRING_LENGTH(string) \
        (NIL_P((string)->rb) ? (string)->length : RSTRING_LEN(string->rb))

#define USTRING_END(string) \
        (NIL_P((string)->rb) ? (string)->c + (string)->length : RSTRING_END(string->rb))

static inline const char *
rb_u_string_begin_from_offset(const UString *string, long offset)
{
        return u_offset_to_pointer_n(offset >= 0 ?
                                        USTRING_STR(string) :
                                        USTRING_END(string),
                                     offset,
                                     USTRING_LENGTH(string));
}


extern VALUE rb_cUString;


VALUE rb_u_string_new(const char *str, long length);
VALUE rb_u_string_new_own(const char *str, long length);
VALUE rb_u_string_new_rb(VALUE str);

const char *rb_u_string_begin_from_offset(const UString *string, long offset);

long rb_u_string_index(VALUE self, VALUE sub, long offset);

VALUE rb_u_string_aref_m(int argc, VALUE *argv, VALUE self);
VALUE rb_u_string_center(int argc, VALUE *argv, VALUE self);
VALUE rb_u_string_casecmp(VALUE self, VALUE other);
VALUE rb_u_string_chomp(int argc, VALUE *argv, VALUE self);
VALUE rb_u_string_chop(VALUE self);
VALUE rb_u_string_collate(VALUE self, VALUE other);
VALUE rb_u_string_count(int argc, VALUE *argv, VALUE self);
VALUE rb_u_string_delete(int argc, VALUE *argv, VALUE self);
VALUE rb_u_string_downcase(VALUE self);
VALUE rb_u_string_dup(VALUE self);
VALUE rb_u_string_each_byte(VALUE self);
VALUE rb_u_string_each_char(VALUE self);
VALUE rb_u_string_each_line(int argc, VALUE *argv, VALUE self);
VALUE rb_u_string_empty(VALUE self);
VALUE rb_u_string_equal(VALUE self, VALUE other);
VALUE rb_u_string_eql(VALUE self, VALUE other);
VALUE rb_u_string_foldcase(VALUE self);
VALUE rb_u_string_hex(VALUE self);
VALUE rb_u_string_index_m(int argc, VALUE *argv, VALUE self);
VALUE rb_u_string_inspect(VALUE self);
VALUE rb_u_string_length(VALUE self);
VALUE rb_u_string_ljust(int argc, VALUE *argv, VALUE self);
VALUE rb_u_string_lstrip(VALUE self);
VALUE rb_u_string_match(VALUE self, VALUE other);
VALUE rb_u_string_normalize(int argc, VALUE *argv, VALUE self);
VALUE rb_u_string_oct(VALUE self);
VALUE rb_u_string_plus(VALUE self, VALUE rbother);
VALUE rb_u_string_reverse(VALUE self);
VALUE rb_u_string_rindex_m(int argc, VALUE *argv, VALUE self);
VALUE rb_u_string_rjust(int argc, VALUE *argv, VALUE self);
VALUE rb_u_string_rstrip(VALUE self);
VALUE rb_u_string_squeeze(int argc, VALUE *argv, VALUE self);
VALUE rb_u_string_strip(VALUE self);
VALUE rb_u_string_times(VALUE self, VALUE rbtimes);
VALUE rb_u_string_to_i(int argc, VALUE *argv, VALUE self);
VALUE rb_u_string_to_str(VALUE self);
VALUE rb_u_string_tr(VALUE self, VALUE from, VALUE to);
VALUE rb_u_string_tr_s(VALUE self, VALUE from, VALUE to);
VALUE rb_u_string_upcase(VALUE self);


void Init_u_string(VALUE mU);


#endif
