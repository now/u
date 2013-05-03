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
        const char *end = string + n;
        struct output output = OUTPUT_INIT(result, m);
        if (n > 0)
                for (const char *p = u_prev(end); p >= string; p = u_prev(p))
                        output_char(&output, u_dref(p));
        return output_finalize(&output);
}
