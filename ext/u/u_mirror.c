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
        const char *end = string + n;
        struct output output = OUTPUT_INIT(result, m);
        for (const char *p = string; p < end; p = u_next(p)) {
                uint32_t c = u_dref(p);
                uint32_t mirrored;
                if (u_char_mirror(c, &mirrored))
                        output_char(&output, mirrored);
                else
                        output_char(&output, c);
        }
        return output_finalize(&output);
}
