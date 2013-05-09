#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "u.h"

#include <assert.h>

#include <string.h>
#include "output.h"

size_t
u_mirror(char *result, size_t m, const char *u, size_t n)
{
	assert(u != NULL);
        assert(result != NULL || m == 0);
        struct output o = OUTPUT_INIT(result, m);
        for (const char *p = u, *end = u + n; p < end; )
                output_char(&o, u_char_mirror(u_decode(&p, p, end)));
        return output_finalize(&o);
}
