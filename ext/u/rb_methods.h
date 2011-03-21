/*
 * contents: Method declarations.
 *
 * Copyright © 2006 Nikolai Weibull <now@bitwi.se>
 */

#ifndef RB_METHODS_H
#define RB_METHODS_H

VALUE rb_u_collate(VALUE str, VALUE other) HIDDEN;
VALUE rb_u_downcase(VALUE str) HIDDEN;
VALUE rb_u_length(VALUE str) HIDDEN;
VALUE rb_u_reverse(VALUE str) HIDDEN;
VALUE rb_u_upcase(VALUE str) HIDDEN;
VALUE rb_u_aref_m(int argc, VALUE *argv, VALUE str) HIDDEN;
VALUE rb_u_aset_m(int argc, VALUE *argv, VALUE str) HIDDEN;
VALUE rb_u_casecmp(VALUE str1, VALUE str2) HIDDEN;
VALUE rb_u_center(int argc, VALUE *argv, VALUE str) HIDDEN;
VALUE rb_u_ljust(int argc, VALUE *argv, VALUE str) HIDDEN;
VALUE rb_u_rjust(int argc, VALUE *argv, VALUE str) HIDDEN;
VALUE rb_u_chomp_bang(int argc, VALUE *argv, VALUE str) HIDDEN;
VALUE rb_u_chomp(int argc, VALUE *argv, VALUE self) HIDDEN;
VALUE rb_u_chop_bang(VALUE str) HIDDEN;
VALUE rb_u_chop(VALUE str) HIDDEN;
VALUE rb_u_count(int argc, VALUE *argv, VALUE str) HIDDEN;
VALUE rb_u_delete_bang(int argc, VALUE *argv, VALUE str) HIDDEN;
VALUE rb_u_delete(int argc, VALUE *argv, VALUE self) HIDDEN;
VALUE rb_u_each_char(VALUE str) HIDDEN;
VALUE rb_u_index_m(int argc, VALUE *argv, VALUE str) HIDDEN;
VALUE rb_u_insert(VALUE str, VALUE index, VALUE other) HIDDEN;
VALUE rb_u_lstrip_bang(VALUE str) HIDDEN;
VALUE rb_u_lstrip(VALUE str) HIDDEN;
VALUE rb_u_rindex_m(int argc, VALUE *argv, VALUE str) HIDDEN;
VALUE rb_u_rstrip_bang(VALUE str) HIDDEN;
VALUE rb_u_rstrip(VALUE str) HIDDEN;
VALUE rb_u_squeeze_bang(int argc, VALUE *argv, VALUE str) HIDDEN;
VALUE rb_u_squeeze(int argc, VALUE *argv, VALUE self) HIDDEN;
VALUE rb_u_strip_bang(VALUE str) HIDDEN;
VALUE rb_u_strip(VALUE str) HIDDEN;
VALUE rb_u_to_i(int argc, VALUE *argv, VALUE str) HIDDEN;
VALUE rb_u_hex(VALUE str) HIDDEN;
VALUE rb_u_oct(VALUE str) HIDDEN;
VALUE rb_u_tr(VALUE str, VALUE from, VALUE to) HIDDEN;
VALUE rb_u_tr_s(VALUE str, VALUE from, VALUE to) HIDDEN;
VALUE rb_u_foldcase(VALUE str) HIDDEN;
VALUE rb_u_normalize(int argc, VALUE *argv, VALUE str) HIDDEN;

#endif /* RB_METHODS_H */
