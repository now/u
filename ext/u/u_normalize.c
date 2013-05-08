#include <ruby.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"

#include "private.h"

#include "data/constants.h"
#include "data/decompose.h"
#include "data/compose.h"

#include "output.h"

enum {
        SBase = 0xac00,
        LBase = 0x1100,
        VBase = 0x1161,
        TBase = 0x11a7,
        LCount = 19,
        VCount = 21,
        TCount = 28,
        NCount = (VCount * TCount),
        SCount = (LCount * NCount),
        SLast = (SBase + SCount - 1)
};


/* Decompose the character ‘s’ according to the rules outlined in
 * http://www.unicode.org/unicode/reports/tr15/#Hangul. */
static inline bool
decompose_hangul(uint32_t s, struct output *output)
{
        if (!(SBase <= s && s <= SLast))
                return false;
        int SIndex = s - SBase;
        uint32_t L = LBase + SIndex / NCount;
        uint32_t V = VBase + (SIndex % NCount) / TCount;
        uint32_t T = TBase + SIndex % TCount;
        output_char(output, L);
        output_char(output, V);
        if (T != TBase)
                output_char(output, T);
        return true;
}

static const char *
compatible(size_t index)
{
        uint16_t offset = decomp_table[index].compat_offset;
        return &decomp_expansion_string[offset == UNICODE_NOT_PRESENT_OFFSET ?
                                        decomp_table[index].canon_offset :
                                        offset];
}

static const char *
canonical(size_t index)
{
        uint16_t offset = decomp_table[index].canon_offset;
        return offset == UNICODE_NOT_PRESENT_OFFSET ?
                NULL :
                &decomp_expansion_string[offset];
}

static inline void
decompose_simple(uint32_t c, const char *(*decompose)(size_t),
                 struct output *output)
{
        size_t index;
        const char *decomposition;
        if (unicode_table_lookup(decomp_table, c, &index) &&
            (decomposition = decompose(index)) != NULL)
                output_zstring(output, decomposition);
        else
                output_char(output, c);
}

static void
decompose_loop(const char *string, const char *end,
               const char *(*decompose)(size_t), struct output *output)
{
        for (const char *p = string; p < end; ) {
                uint32_t c = u_decode(&p, p, end);
                if (!decompose_hangul(c, output))
                        decompose_simple(c, decompose, output);
        }
}

static inline void
canonical_ordering_swap(char *string, char *p,
                        enum u_canonical_combining_class ccc)
{
        char *r = p;
        char *s;
        const char *t;
        while (r > string && (s = u_prev(r), u_char_canonical_combining_class(u_decode(&t, s, r)) > ccc))
                r = s;
        char buf[U_CHAR_MAX_BYTE_LENGTH];
        size_t n = u_next(p) - p;
        memcpy(buf, p, n);
        memmove(r + n, r, p - r);
        memcpy(r, buf, n);
}

static inline bool
canonical_ordering_reorder(char *string, char *end)
{
        bool swapped = false;
        char *p;
        uint32_t c = u_decode((const char **)&p, string, end);
        enum u_canonical_combining_class pcc = u_char_canonical_combining_class(c);
        while (p < end) {
                char *q;
                enum u_canonical_combining_class cc = u_char_canonical_combining_class(u_decode((const char **)&q, p, end));

                if (cc != 0 && pcc > cc) {
                        canonical_ordering_swap(string, p, cc);
                        swapped = true;
                } else
                        pcc = cc;
                p = q;
        }
        return swapped;
}

static void
canonical_ordering(char *string, size_t n)
{
        char *end = string + n;
        while (canonical_ordering_reorder(string, end))
                ;
}

static inline bool
compose_hangul(uint32_t a, uint32_t b, uint32_t *result)
{
        int LIndex = a - LBase;
        if (0 <= LIndex && LIndex < LCount) {
                int VIndex = b - VBase;
                if (0 <= VIndex && VIndex < VCount) {
                        *result = SBase + (LIndex * VCount + VIndex) * TCount;

                        return true;
                }
        }

        int SIndex = a - SBase;
        if (0 <= SIndex && SIndex < SCount && (SIndex % TCount) == 0) {
                int TIndex = b - TBase;
                if (0 < TIndex && TIndex < TCount) {
                        *result = a + TIndex;

                        return true;
                }
        }

        return false;
}

static inline uint16_t
compose_index(uint32_t c)
{
        unsigned int page = c >> 8;

        if (page > COMPOSE_TABLE_LAST)
                return 0;

        int16_t index = compose_table[page];

        if (index >= UNICODE_MAX_TABLE_INDEX)
                return index - UNICODE_MAX_TABLE_INDEX;

        return compose_data[index][c & 0xff];
}

static inline bool
compose(uint32_t a, uint32_t b, uint32_t *result)
{
        if (compose_hangul(a, b, result))
                return true;

        uint16_t index_a = compose_index(a);
        if (COMPOSE_FIRST_SINGLE_START <= index_a && index_a < COMPOSE_SECOND_START) {
                if (b != compose_first_single[index_a - COMPOSE_FIRST_SINGLE_START][0])
                        return false;
                *result = compose_first_single[index_a - COMPOSE_FIRST_SINGLE_START][1];
                return true;
        }

        uint16_t index_b = compose_index(b);
        if (COMPOSE_SECOND_SINGLE_START <= index_b) {
                if (a != compose_second_single[index_b - COMPOSE_SECOND_SINGLE_START][0])
                        return false;
                *result = compose_second_single[index_b - COMPOSE_SECOND_SINGLE_START][1];
                return true;
        }

        if (COMPOSE_FIRST_START <= index_a && index_a < COMPOSE_FIRST_SINGLE_START &&
            COMPOSE_SECOND_START <= index_b && index_b < COMPOSE_SECOND_SINGLE_START) {
                uint32_t r = compose_array[index_a - COMPOSE_FIRST_START][index_b - COMPOSE_SECOND_START];
                if (r != 0) {
                        *result = r;
                        return true;
                }
        }

        return false;
}

static inline size_t
compose_loop(char *string, size_t n)
{
        int pcc = -1;
        char *s = string;
        char *t = u_next(s);
        for (char *p = t, *q, *end = string + n; p < end; p = q) {
                uint32_t c = u_decode((const char **)&q, p, end);
                int cc = u_char_canonical_combining_class(c);
                const char *ignored;
                uint32_t b = u_decode(&ignored, s, t), d;
                if (pcc < cc && compose(b, c, &d)) {
                        char *r = u_next(s);
                        ptrdiff_t k = u_char_to_u(d, NULL) - (r - s);
                        memmove(r + k, r, t - r);
                        u_char_to_u(d, s);
                        t += k;
                } else if (cc == 0) {
                        pcc = -1;
                        s = t;
                        t += u_char_to_u(c, t);
                } else {
                        pcc = cc;
                        t += u_char_to_u(c, t);
                }
        }
        return t - string;
}

size_t
u_normalize(char *result, size_t m, const char *string, size_t n,
            enum u_normalization_form form)
{
        const char *(*decompose)(size_t) =
                (form == U_NORMALIZATION_FORM_KC ||
                 form == U_NORMALIZATION_FORM_KD) ? compatible : canonical;
        const char *end = string + n;
        struct output output = OUTPUT_INIT(result, m);
        decompose_loop(string, end, decompose, &output);
        if (output.m > output.n && output.n > 0) {
                canonical_ordering(output.result, output.n);
                if (form == U_NORMALIZATION_FORM_C ||
                    form == U_NORMALIZATION_FORM_KC)
                        output.n = compose_loop(output.result, output.n);
        }
        return output_finalize(&output);
}
