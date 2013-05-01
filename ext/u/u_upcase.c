#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "attributes.h"
#include "titled.h"
#include "output.h"
#include "u_locale.h"
#include "case.h"

#define LATIN_SMALL_LETTER_I ((uint32_t)0x0069)
#define LATIN_CAPITAL_LETTER_I_WITH_DOT_ABOVE ((uint32_t)0x0130)
#define COMBINING_DOT_ABOVE ((uint32_t)0x0307)
#define COMBINING_GREEK_YPOGEGRAMMENI ((uint32_t)0x0345)
#define GREEK_CAPITAL_LETTER_IOTA ((uint32_t)0x0399)


static inline bool
ismark(int category)
{
        return IS(category,
                  OR(U_GENERAL_CATEGORY_MARK_NON_SPACING,
                     OR(U_GENERAL_CATEGORY_MARK_SPACING_COMBINING,
                        OR(U_GENERAL_CATEGORY_MARK_ENCLOSING, 0))));
}

static inline const char *
output_marks(const char *p, const char *end, bool use_end, struct output *output)
{
        const char *q = u_next(p);
        while (P_WITHIN_STR(q, end, use_end)) {
		uint32_t c = u_dref(q);
                if (!ismark(u_char_general_category(c)))
                        break;
                output_char(output, c);
                q = u_next(q);
	}
        return u_prev(q);
}

void
_u_upcase_step(const char *string, const char **p, const char *end, bool use_end,
               enum locale locale, bool title, struct output *output)
{
        uint32_t c = u_dref(*p);
        enum u_general_category gc;
        if (!title && c == COMBINING_GREEK_YPOGEGRAMMENI) {
                *p = output_marks(*p, end, use_end, output);
                output_char(output, GREEK_CAPITAL_LETTER_IOTA);
        } else if (locale == LOCALE_LITHUANIAN &&
                   c == COMBINING_DOT_ABOVE &&
                   is_after(string, *p, u_char_issoftdotted))
                ;
        else if (locale == LOCALE_TURKIC && c == LATIN_SMALL_LETTER_I)
                output_char(output, LATIN_CAPITAL_LETTER_I_WITH_DOT_ABOVE);
        else if (IS(gc = u_char_general_category(c),
                    OR(U_GENERAL_CATEGORY_LETTER_LOWERCASE,
                       OR(U_GENERAL_CATEGORY_LETTER_TITLECASE, 0))))
                case_simple(c, gc,
                            title || gc != U_GENERAL_CATEGORY_LETTER_LOWERCASE,
                            true,
                            output);
        else
                output_string(output, *p, u_next(*p) - *p);
}

static void
upcase_loop(const char *string, const char *end, bool use_end,
            enum locale locale, struct output *output)
{
	for (const char *p = string; P_WITHIN_STR(p, end, use_end); p = u_next(p))
                _u_upcase_step(string, &p, end, use_end, locale, false, output);
}

static char *
u_upcase_in_locale_impl(const char *string, size_t n, bool use_n,
                        const char *locale, size_t *new_n)
{
	assert(string != NULL);
	enum locale l = _u_locale_from_string(locale);
        const char *end = string + n;
        struct output output = OUTPUT_INIT;
	upcase_loop(string, end, use_n, l, &output);
        output_alloc(&output);
	upcase_loop(string, end, use_n, l, &output);
        return output_finalize(&output, new_n);
}

char *
u_upcase(const char *string)
{
	return u_upcase_in_locale_impl(string, 0, false, NULL, NULL);
}

char *
u_upcase_n(const char *string, size_t n, size_t *new_n)
{
	return u_upcase_in_locale_impl(string, n, true, NULL, new_n);
}

char *
u_upcase_in_locale(const char *string, const char *locale)
{
	return u_upcase_in_locale_impl(string, 0, false, locale, NULL);
}

char *
u_upcase_in_locale_n(const char *string, size_t n, const char *locale,
                     size_t *new_n)
{
	return u_upcase_in_locale_impl(string, n, true, locale, new_n);
}
