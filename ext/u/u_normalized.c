#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"

enum u_normalized
u_normalized(const char *string, size_t n, enum u_normalization_form form)
{
        enum u_canonical_combining_class pcc = 0;
        enum u_normalized r = U_NORMALIZED_YES;
        for (const char *p = string, *end = string + n; p < end; ) {
                uint32_t c = u_decode(&p, p, end);
                enum u_canonical_combining_class cc = u_char_canonical_combining_class(c);
                if (pcc > cc && cc != 0)
                        return U_NORMALIZED_NO;
                switch (u_char_normalized(c, form)) {
                case U_NORMALIZED_NO:
                        return U_NORMALIZED_NO;
                case U_NORMALIZED_MAYBE:
                        r = U_NORMALIZED_MAYBE;
                        break;
                case U_NORMALIZED_YES:
                        break;
                }
                pcc = cc;
        }
        return r;
}
