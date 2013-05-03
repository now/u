#include <ruby.h>
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"

#include "private.h"

#include "data/case-folding.h"
#include "output.h"


size_t
u_foldcase(char *result, size_t m, const char *string, size_t n)
{
	assert(string != NULL);
        assert(result != NULL || m == 0);
        const char *end = string + n;
        struct output output = OUTPUT_INIT(result, m);
        for (const char *p = string; p < end; p = u_next(p)) {
		uint32_t c = u_dref(p);
                size_t i;
                if (unicode_table_lookup(casefold_table, c, &i))
                        output_zstring(&output, casefold_table[i].data);
                else
                        output_char(&output, u_char_downcase(c));
        }
        return output_finalize(&output);
}
