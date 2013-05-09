#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "u.h"
#include "private.h"
#include "output.h"


size_t
u_reverse(char *result, size_t m, const char *string, size_t n)
{
	assert(string != NULL);
        assert(result != NULL || m == 0);
        struct output output = OUTPUT_INIT(result, m);
        for (const char *p = string + n; p > string; )
                output_char(&output, u_decode_r(&p, string, p));
        return output_finalize(&output);
}
