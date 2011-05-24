#ifndef RB_U_BUFFER_H
#define RB_U_BUFFER_H


VALUE rb_u_buffer_new(void);
VALUE rb_u_buffer_new_sized(long size);

VALUE rb_u_buffer_append(VALUE self, const char *str, long length);
VALUE rb_u_buffer_append_format(int argc, const VALUE *argv, VALUE self, VALUE format);
VALUE rb_u_buffer_append_format_m(int argc, const VALUE *argv, VALUE self);
VALUE rb_u_buffer_append_unichar(VALUE self, unichar c);
VALUE rb_u_buffer_append_unichar_n(VALUE self, unichar c, long n);

VALUE rb_u_buffer_append_m(int argc, VALUE *argv, VALUE self);
VALUE rb_u_buffer_eql(VALUE self, VALUE rbother);
VALUE rb_u_buffer_hash(VALUE self);
VALUE rb_u_buffer_to_s(VALUE self);
VALUE rb_u_buffer_to_u(VALUE self);
VALUE rb_u_buffer_to_u_bang(VALUE self);

void Init_u_buffer(VALUE mU);


#endif
