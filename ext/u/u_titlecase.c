#include <ruby.h>
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "u.h"
#include "private.h"
#include "data/constants.h"
#include "attributes.h"
#include "titled.h"
#include "output.h"
#include "u_locale.h"
#include "case.h"

#define LATIN_CAPITAL_LETTER_I ((uint32_t)0x0049)
#define LATIN_CAPITAL_LETTER_J ((uint32_t)0x004a)
#define LATIN_SMALL_LETTER_I ((uint32_t)0x0069)
#define LATIN_SMALL_LETTER_J ((uint32_t)0x006a)

struct titlecase_closure {
        const char *string;
        enum locale locale;
        struct output *output;
};

static void
titlecase_step(const char *p, const char *q, struct titlecase_closure *closure)
{
        const char *t = p;
        uint32_t c;
        const char *u;
        while (t < q && (u = u_decode(&c, t, q), !u_char_iscased(c)))
                t = u;
        output_string(closure->output, p, t - p);
        if (t == q)
                return;
        _u_upcase_step(closure->string, t, q, closure->locale, true,
                       closure->output);
        if (t + 1 < q && closure->locale == LOCALE_DUTCH &&
            (*t == LATIN_CAPITAL_LETTER_I || *t == LATIN_SMALL_LETTER_I) &&
            (*(t + 1) == LATIN_CAPITAL_LETTER_J || *(t + 1) == LATIN_SMALL_LETTER_J)) {
                output_char(closure->output, LATIN_CAPITAL_LETTER_J);
                t++;
        }
        for (t = u_next(t); t < q; t = u_next(t))
                _u_downcase_step(closure->string, t, q, closure->locale,
                                 closure->output);
}

static void
titlecase_words(const char *p, size_t n, struct titlecase_closure *closure)
{
        titlecase_step(p, p + n, closure);
}

size_t
u_titlecase(char *result, size_t m, const char *string, size_t n,
            const char *locale)
{
	assert(string != NULL);
        assert(result != NULL || m == 0);
        struct output output = OUTPUT_INIT(result, m);
        struct titlecase_closure closure =
                { string, _u_locale_from_string(locale), &output };
        u_words(string, n, (u_substring_fn)titlecase_words, &closure);
        return output_finalize(&output);
}
