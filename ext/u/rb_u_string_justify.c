#include "rb_includes.h"

static char *
rb_u_string_justify_one_side(char *p, const char *f, long f_len, long f_size, long n)
{
        long i;
        for (i = 0; i + f_len < n; i += f_len, p += f_size)
                memcpy(p, f, f_size);

        const char *q = f;
        while (i < n) {
                const char *q_end = u_next(q);
                memcpy(p, q, q_end - q);
                p += q_end - q;
                q = q_end;
                i++;
        }

        return p;
}

static VALUE
rb_u_string_justify(int argc, VALUE *argv, VALUE str, char jflag)
{
        VALUE w, pad;
        const char *f = " ";
        long f_len = 1;
        long f_size = 1;
        bool infect_from_pad = false;

        if (rb_scan_args(argc, argv, "11", &w, &pad) == 2) {
                StringValue(pad);
                f = RSTRING(pad)->ptr;
                f_len = u_length_n(f, RSTRING(pad)->len);
                if (f_len == 0)
                        rb_raise(rb_eArgError, "zero width padding");
                f_size = RSTRING(pad)->len;
                infect_from_pad = true;
        }

        long len = u_length_n(RSTRING(str)->ptr, RSTRING(str)->len);

        long width = NUM2LONG(w);
        if (width < 0 || len >= width)
                return rb_u_string_dup(str);

        VALUE res = rb_u_string_new5(str, 0, RSTRING(str)->len + (width - len) * f_size);
        char *p = RSTRING(res)->ptr;

        long n_remaining = width - len;
        if (jflag != 'l') {
                long n = n_remaining;
                if (jflag == 'c')
                        n /= 2;
                n_remaining -= n;

                p = rb_u_string_justify_one_side(p, f, f_len, f_size, n);
        }

        memcpy(p, RSTRING(str)->ptr, RSTRING(str)->len);
        p += RSTRING(str)->len;

        if (jflag != 'r')
                p = rb_u_string_justify_one_side(p, f, f_len, f_size, n_remaining);

        OBJ_INFECT(res, str);

        if (infect_from_pad)
                OBJ_INFECT(res, pad);

        return res;
}

VALUE
rb_u_string_center(int argc, VALUE *argv, VALUE str)
{
        return rb_u_string_justify(argc, argv, str, 'c');
}

VALUE
rb_u_string_ljust(int argc, VALUE *argv, VALUE str)
{
        return rb_u_string_justify(argc, argv, str, 'l');
}

VALUE
rb_u_string_rjust(int argc, VALUE *argv, VALUE str)
{
        return rb_u_string_justify(argc, argv, str, 'r');
}
