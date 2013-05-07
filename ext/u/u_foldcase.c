#include <ruby.h>
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"

#include "private.h"

#include "data/case-folding.h"
#include "output.h"
#include "u_locale.h"

static inline void
foldcase_step(uint32_t c, struct output *output)
{
        size_t i;
        if (unicode_table_lookup(casefold_table, c, &i))
                output_zstring(output, casefold_table[i].data);
        else
                output_char(output, u_char_downcase(c));
}

#define LATIN_CAPITAL_LETTER_I ((uint32_t)0x0049)
#define LATIN_SMALL_LETTER_DOTLESS_I ((uint32_t)0x0131)
#define LATIN_CAPITAL_LETTER_I_WITH_DOT_ABOVE ((uint32_t)0x0130)
#define LATIN_SMALL_LETTER_I ((uint32_t)0x0069)

static inline void
foldcase_step_turkic(uint32_t c, struct output *output)
{
        if (c == LATIN_CAPITAL_LETTER_I)
                output_char(output, LATIN_SMALL_LETTER_DOTLESS_I);
        else if (c == LATIN_CAPITAL_LETTER_I_WITH_DOT_ABOVE)
                output_char(output, LATIN_SMALL_LETTER_I);
        else
                foldcase_step(c, output);
}

size_t
u_foldcase(char *result, size_t m, const char *string, size_t n,
           const char *locale)
{
	assert(string != NULL);
        assert(result != NULL || m == 0);
	enum locale l = _u_locale_from_string(locale);
        const char *end = string + n;
        struct output output = OUTPUT_INIT(result, m);
        if (l == LOCALE_TURKIC)
                for (const char *p = string; p < end; p = u_next(p))
                        foldcase_step_turkic(u_dref(p), &output);
        else
                for (const char *p = string; p < end; p = u_next(p))
                        foldcase_step(u_dref(p), &output);
        return output_finalize(&output);
}
