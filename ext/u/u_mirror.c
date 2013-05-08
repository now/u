#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "u.h"
#include "private.h"

#include "output.h"

size_t
u_mirror(char *result, size_t m, const char *string, size_t n)
{
	assert(string != NULL);
        assert(result != NULL || m == 0);
        struct output output = OUTPUT_INIT(result, m);
        for (const char *p = string, *end = string + n; p < end; ) {
                uint32_t c;
                p = u_decode(&c, p, end);
                uint32_t mirrored;
                if (u_char_mirror(c, &mirrored))
                        output_char(&output, mirrored);
                else
                        output_char(&output, c);
        }
        return output_finalize(&output);
}
