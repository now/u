#include "rb_includes.h"
#ifdef HAVE_RUBY_ENCODING_H
#  include <ruby/encoding.h>
#endif

#ifndef HAVE_RB_MEMHASH
int
rb_memhash(const char *string, long length)
{
        const char *p = string;
        const char *end = string + length;
        int hash = 0;

        while (p < end) {
                hash = hash * 65599 + *p;
                p++;
        }

        return hash + (hash >> 5);
}
#endif

long
rb_u_memsearch(const void *a, long a_n, const void *b, long b_n)
{
#ifdef HAVE_RUBY_ENCODING_H
        return rb_memsearch(a, a_n, b, b_n, rb_utf8_encoding());
#else
        return rb_memsearch(a, a_n, b, b_n);
#endif
}

void
rb_u_raise(VALUE exception, const char *format, ...)
{
        va_list args;
        VALUE message;

        va_start(args, format);
#ifdef HAVE_RUBY_ENCODING_H
        message = rb_enc_vsprintf(rb_utf8_encoding(), format, args);
#else
        message = rb_vsprintf(format, args);
#endif
        va_end(args);

        rb_exc_raise(rb_exc_new3(exception, message));
}

void
rb_u_raise_errno(VALUE exception, int number, const char *format, ...)
{
        va_list args;
        VALUE message;

        va_start(args, format);
#ifdef HAVE_RUBY_ENCODING_H
        message = rb_enc_vsprintf(rb_utf8_encoding(), format, args);
#else
#  ifdef HAVE_RB_VSPRINTF
        message = rb_vsprintf(format, args);
#  else
        char *buf;
        int n = vsnprintf(buf, 0, format, args);
        buf = ALLOC_N(char, n + 1);
        vsnprintf(buf, n + 1, format, args);
        message = rb_str_new(buf, n);
        free(buf);
#  endif
#endif
        va_end(args);

        VALUE error = rb_str_new2(strerror(number));
#ifdef HAVE_RUBY_ENCODING_H
        rb_enc_associate(error, rb_locale_encoding());
        error = rb_str_encode(error, rb_enc_from_encoding(rb_utf8_encoding()), 0, Qnil);
#endif

        rb_exc_raise(rb_exc_new3(exception,
                                 rb_str_append(rb_str_append(message, rb_str_new2(": ")),
                                               error)));
}

VALUE
rb_u_str_new(const char *string, long length)
{
#ifdef HAVE_RUBY_ENCODING_H
        return rb_enc_str_new(string, length, rb_utf8_encoding());
#else
        return rb_str_new(string, length);
#endif
}

VALUE
rb_u_str_buf_new(long length)
{
#ifdef HAVE_RUBY_ENCODING_H
        VALUE buffer = rb_str_buf_new(length);
        rb_enc_associate(buffer, rb_utf8_encoding());
        return buffer;
#else
        return rb_str_buf_new(length);
#endif
}
