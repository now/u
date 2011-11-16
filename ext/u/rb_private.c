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
