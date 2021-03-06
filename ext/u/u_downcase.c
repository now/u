#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "u.h"

#include <assert.h>

#include <string.h>
#include "output.h"

#include "data/constants.h"
#include "attributes.h"
#include "u_locale.h"
#include "titled.h"
#include "case.h"
#include "private.h"

#define LATIN_CAPITAL_LETTER_I ((uint32_t)0x0049)
#define LATIN_CAPITAL_LETTER_J ((uint32_t)0x004a)
#define LATIN_SMALL_LETTER_I ((uint32_t)0x0069)
#define LATIN_CAPITAL_LETTER_I_WITH_GRAVE ((uint32_t)0x00cc)
#define LATIN_CAPITAL_LETTER_I_WITH_ACUTE ((uint32_t)0x00cd)
#define LATIN_CAPITAL_LETTER_I_WITH_TILDE ((uint32_t)0x0128)
#define LATIN_CAPITAL_LETTER_I_WITH_OGONEK ((uint32_t)0x012e)
#define LATIN_CAPITAL_LETTER_I_WITH_DOT_ABOVE ((uint32_t)0x0130)
#define LATIN_SMALL_LETTER_DOTLESS_I ((uint32_t)0x0131)
#define COMBINING_GRAVE_ACCENT ((uint32_t)0x0300)
#define COMBINING_ACUTE_ACCENT ((uint32_t)0x0301)
#define COMBINING_TILDE ((uint32_t)0x0303)
#define COMBINING_DOT_ABOVE ((uint32_t)0x0307)
#define GREEK_CAPITAL_LETTER_SIGMA ((uint32_t)0x03a3)
#define GREEK_SMALL_LETTER_FINAL_SIGMA ((uint32_t)0x03c2)
#define GREEK_SMALL_LETTER_SIGMA ((uint32_t)0x03c3)


static inline bool
is_final_sigma(const char *string, const char *p, const char *q, const char *end)
{
        if (p == string)
                return false;
        uint32_t c;
        while (q < end) {
                c = u_decode(&q, q, end);
                if (u_char_iscaseignorable(c))
                        continue;
                if (u_char_iscased(c))
                        return false;
                break;
        }
        while (string < p) {
                c = u_decode_r(&p, string, p);
                if (u_char_iscaseignorable(c))
                        continue;
                if (u_char_iscased(c))
                        return true;
                return false;
        }
        return false;
}

static inline bool
has_more_above(const char *q, const char *end)
{
        while (q < end) {
		switch (u_char_canonical_combining_class(u_decode(&q, q, end))) {
                case U_CANONICAL_COMBINING_CLASS_ABOVE:
			return true;
                case U_CANONICAL_COMBINING_CLASS_NOT_REORDERED:
			return false;
                default:
                        break;
                }
	}
	return false;
}

static bool
downcase_lithuanian_i(uint32_t c, uint32_t combiner, struct output *output)
{
        output_char(output, c);
        output_char(output, COMBINING_DOT_ABOVE);
        if (combiner != '\0')
                output_char(output, combiner);
        return true;
}

static inline bool
downcase_lithuanian(uint32_t c, const char *q, const char *end,
                    struct output *output)
{
        switch (c) {
        case LATIN_CAPITAL_LETTER_I:
        case LATIN_CAPITAL_LETTER_J:
        case LATIN_CAPITAL_LETTER_I_WITH_OGONEK:
                if (!has_more_above(q, end))
                        return false;
                return downcase_lithuanian_i(u_char_downcase(c), '\0', output);
        case LATIN_CAPITAL_LETTER_I_WITH_GRAVE:
                return downcase_lithuanian_i(LATIN_SMALL_LETTER_I,
                                             COMBINING_GRAVE_ACCENT, output);
        case LATIN_CAPITAL_LETTER_I_WITH_ACUTE:
                return downcase_lithuanian_i(LATIN_SMALL_LETTER_I,
                                             COMBINING_ACUTE_ACCENT, output);
        case LATIN_CAPITAL_LETTER_I_WITH_TILDE:
                return downcase_lithuanian_i(LATIN_SMALL_LETTER_I,
                                             COMBINING_TILDE, output);
        default:
                return false;
        }
}

static inline bool
is_before_dot(const char *q, const char *end)
{
        while (q < end) {
                uint32_t c = u_decode(&q, q, end);
                if (c == COMBINING_DOT_ABOVE)
                        return true;
                switch (u_char_canonical_combining_class(c)) {
                case U_CANONICAL_COMBINING_CLASS_ABOVE:
                case U_CANONICAL_COMBINING_CLASS_NOT_REORDERED:
                        return false;
                default:
                        break;
                }
	}
        return false;
}

static bool
is_i(uint32_t c)
{
        return c == LATIN_CAPITAL_LETTER_I;
}

static inline bool
downcase_turkic(uint32_t c,
                const char *string, const char *p, const char *q, const char *end,
                struct output *output)
{
        switch (c) {
        case LATIN_CAPITAL_LETTER_I:
                output_char(output,
                            is_before_dot(q, end) ?
                            LATIN_SMALL_LETTER_I :
                            LATIN_SMALL_LETTER_DOTLESS_I);
                return true;
        case LATIN_CAPITAL_LETTER_I_WITH_DOT_ABOVE:
                case_simple(LATIN_CAPITAL_LETTER_I,
                            U_GENERAL_CATEGORY_LETTER_UPPERCASE,
                            false, false, output);
                return true;
        case COMBINING_DOT_ABOVE:
                if (!is_after(string, p, is_i))
                        output_char(output, COMBINING_DOT_ABOVE);
                return true;
        default:
                return false;
        }
}

const char *
_u_downcase_step(const char *string, const char *p, const char *end,
                 enum locale locale, struct output *output)
{
        const char *q;
        uint32_t c = u_decode(&q, p, end);
        enum u_general_category gc;
        if (c == GREEK_CAPITAL_LETTER_SIGMA)
                output_char(output,
                            is_final_sigma(string, p, q, end) ?
                            GREEK_SMALL_LETTER_FINAL_SIGMA :
                            GREEK_SMALL_LETTER_SIGMA);
        else if (locale == LOCALE_LITHUANIAN &&
                 downcase_lithuanian(c, q, end, output))
                ;
        else if (locale == LOCALE_TURKIC &&
                 downcase_turkic(c, string, p, q, end, output))
                ;
        else if (IS(gc = u_char_general_category(c),
                    OR(U_GENERAL_CATEGORY_LETTER_UPPERCASE,
                       OR(U_GENERAL_CATEGORY_LETTER_TITLECASE, 0))))
                case_simple(c, gc, false, false, output);
        else
                output_string(output, p, q - p);
        return q;
}

size_t
u_downcase(char *result, size_t m, const char *u, size_t n,
           const char *locale)
{
	assert(u != NULL);
        assert(result != NULL || m == 0);
	enum locale l = _u_locale_from_string(locale);
        const char *end = u + n;
        struct output o = OUTPUT_INIT(result, m);
        for (const char *p = u; p < end; )
                p = _u_downcase_step(u, p, end, l, &o);
        return output_finalize(&o);
}
