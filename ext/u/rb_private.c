#include "rb_includes.h"

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
