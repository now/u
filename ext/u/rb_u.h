/*
 * contents: Method declarations.
 *
 * Copyright © 2006 Nikolai Weibull <now@bitwi.se>
 */

#ifndef RB_U_H
#define RB_U_H

VALUE rb_u_string_collate(VALUE str, VALUE other) HIDDEN;
VALUE rb_u_string_downcase(VALUE str) HIDDEN;
VALUE rb_u_string_length(VALUE str) HIDDEN;
VALUE rb_u_string_reverse(VALUE str) HIDDEN;
VALUE rb_u_string_upcase(VALUE str) HIDDEN;
VALUE rb_u_string_aref_m(int argc, VALUE *argv, VALUE str) HIDDEN;
VALUE rb_u_string_aset_m(int argc, VALUE *argv, VALUE str) HIDDEN;
VALUE rb_u_string_casecmp(VALUE str1, VALUE str2) HIDDEN;
VALUE rb_u_string_center(int argc, VALUE *argv, VALUE str) HIDDEN;
VALUE rb_u_string_ljust(int argc, VALUE *argv, VALUE str) HIDDEN;
VALUE rb_u_string_rjust(int argc, VALUE *argv, VALUE str) HIDDEN;
VALUE rb_u_string_chomp_bang(int argc, VALUE *argv, VALUE str) HIDDEN;
VALUE rb_u_string_chomp(int argc, VALUE *argv, VALUE self) HIDDEN;
VALUE rb_u_string_chop_bang(VALUE str) HIDDEN;
VALUE rb_u_string_chop(VALUE str) HIDDEN;
VALUE rb_u_string_count(int argc, VALUE *argv, VALUE str) HIDDEN;
VALUE rb_u_string_delete_bang(int argc, VALUE *argv, VALUE str) HIDDEN;
VALUE rb_u_string_delete(int argc, VALUE *argv, VALUE self) HIDDEN;
VALUE rb_u_string_each_char(VALUE str) HIDDEN;
VALUE rb_u_string_index_m(int argc, VALUE *argv, VALUE str) HIDDEN;
VALUE rb_u_string_insert(VALUE str, VALUE index, VALUE other) HIDDEN;
VALUE rb_u_string_lstrip_bang(VALUE str) HIDDEN;
VALUE rb_u_string_lstrip(VALUE str) HIDDEN;
VALUE rb_u_string_rindex_m(int argc, VALUE *argv, VALUE str) HIDDEN;
VALUE rb_u_string_rstrip_bang(VALUE str) HIDDEN;
VALUE rb_u_string_rstrip(VALUE str) HIDDEN;
VALUE rb_u_string_squeeze_bang(int argc, VALUE *argv, VALUE str) HIDDEN;
VALUE rb_u_string_squeeze(int argc, VALUE *argv, VALUE self) HIDDEN;
VALUE rb_u_string_strip_bang(VALUE str) HIDDEN;
VALUE rb_u_string_strip(VALUE str) HIDDEN;
VALUE rb_u_string_to_i(int argc, VALUE *argv, VALUE str) HIDDEN;
VALUE rb_u_string_hex(VALUE str) HIDDEN;
VALUE rb_u_string_oct(VALUE str) HIDDEN;
VALUE rb_u_string_tr(VALUE str, VALUE from, VALUE to) HIDDEN;
VALUE rb_u_string_tr_s(VALUE str, VALUE from, VALUE to) HIDDEN;
VALUE rb_u_string_foldcase(VALUE str) HIDDEN;
VALUE rb_u_string_normalize(int argc, VALUE *argv, VALUE str) HIDDEN;

#endif /* RB_U_H */
