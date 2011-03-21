/*
 * contents: Method declarations.
 *
 * Copyright © 2006 Nikolai Weibull <now@bitwi.se>
 */

#ifndef RB_METHODS_H
#define RB_METHODS_H

VALUE rb_utf_collate(VALUE str, VALUE other) HIDDEN;
VALUE rb_utf_downcase(VALUE str) HIDDEN;
VALUE rb_utf_length(VALUE str) HIDDEN;
VALUE rb_utf_reverse(VALUE str) HIDDEN;
VALUE rb_utf_upcase(VALUE str) HIDDEN;
VALUE rb_utf_aref_m(int argc, VALUE *argv, VALUE str) HIDDEN;
VALUE rb_utf_aset_m(int argc, VALUE *argv, VALUE str) HIDDEN;
VALUE rb_utf_casecmp(VALUE str1, VALUE str2) HIDDEN;
VALUE rb_utf_center(int argc, VALUE *argv, VALUE str) HIDDEN;
VALUE rb_utf_ljust(int argc, VALUE *argv, VALUE str) HIDDEN;
VALUE rb_utf_rjust(int argc, VALUE *argv, VALUE str) HIDDEN;
VALUE rb_utf_chomp_bang(int argc, VALUE *argv, VALUE str) HIDDEN;
VALUE rb_utf_chomp(int argc, VALUE *argv, VALUE self) HIDDEN;
VALUE rb_utf_chop_bang(VALUE str) HIDDEN;
VALUE rb_utf_chop(VALUE str) HIDDEN;
VALUE rb_utf_count(int argc, VALUE *argv, VALUE str) HIDDEN;
VALUE rb_utf_delete_bang(int argc, VALUE *argv, VALUE str) HIDDEN;
VALUE rb_utf_delete(int argc, VALUE *argv, VALUE self) HIDDEN;
VALUE rb_utf_each_char(VALUE str) HIDDEN;
VALUE rb_utf_index_m(int argc, VALUE *argv, VALUE str) HIDDEN;
VALUE rb_utf_insert(VALUE str, VALUE index, VALUE other) HIDDEN;
VALUE rb_utf_lstrip_bang(VALUE str) HIDDEN;
VALUE rb_utf_lstrip(VALUE str) HIDDEN;
VALUE rb_utf_rindex_m(int argc, VALUE *argv, VALUE str) HIDDEN;
VALUE rb_utf_rstrip_bang(VALUE str) HIDDEN;
VALUE rb_utf_rstrip(VALUE str) HIDDEN;
VALUE rb_utf_squeeze_bang(int argc, VALUE *argv, VALUE str) HIDDEN;
VALUE rb_utf_squeeze(int argc, VALUE *argv, VALUE self) HIDDEN;
VALUE rb_utf_strip_bang(VALUE str) HIDDEN;
VALUE rb_utf_strip(VALUE str) HIDDEN;
VALUE rb_utf_to_i(int argc, VALUE *argv, VALUE str) HIDDEN;
VALUE rb_utf_hex(VALUE str) HIDDEN;
VALUE rb_utf_oct(VALUE str) HIDDEN;
VALUE rb_utf_tr(VALUE str, VALUE from, VALUE to) HIDDEN;
VALUE rb_utf_tr_s(VALUE str, VALUE from, VALUE to) HIDDEN;
VALUE rb_utf_foldcase(VALUE str) HIDDEN;
VALUE rb_utf_normalize(int argc, VALUE *argv, VALUE str) HIDDEN;

#endif /* RB_METHODS_H */
