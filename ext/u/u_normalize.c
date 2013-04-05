#include <ruby.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"

#include "private.h"

#include "data/constants.h"
#include "data/decompose.h"
#include "data/compose.h"

#include "combining_class.h"


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
static size_t
decompose_hangul(uint32_t s, uint32_t *result)
{
        int SIndex = s - SBase;

        if (SIndex < 0 || SIndex >= SCount) {
                if (result != NULL)
                        result[0] = s;

                return 1;
        }

        uint32_t L = LBase + SIndex / NCount;
        uint32_t V = VBase + (SIndex % NCount) / TCount;
        uint32_t T = TBase + SIndex % TCount;

        if (result != NULL) {
                result[0] = L;
                result[1] = V;
        }

        if (T == TBase)
                return 2;

        if (result != NULL)
                result[2] = T;

        return 3;
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

static inline size_t
decomposition_to_wc(const char *decomposition, uint32_t *result)
{
        size_t i = 0;

        for (const char *p = decomposition; *p != '\0'; p = u_next(p))
                result[i++] = u_dref(p);

        return i;
}

static size_t
decompose_simple(uint32_t c, const char *(*decompose)(size_t), uint32_t *result)
{
        size_t index;
        const char *decomposition;
        if (!unicode_table_lookup(decomp_table, c, &index) ||
            (decomposition = decompose(index)) == NULL) {
                if (result != NULL)
                        result[0] = c;

                return 1;
        }

        if (result != NULL)
                return decomposition_to_wc(decomposition, result);

        return u_n_chars(decomposition);
}

static inline size_t
decompose_step(uint32_t c, const char *(*decompose)(size_t), uint32_t *result)
{
        return (SBase <= c && c <= SLast) ?
                decompose_hangul(c, result) :
                decompose_simple(c, decompose, result);
}

static size_t
decompose_loop(const char *string, size_t length, bool use_length,
               const char *(*decompose)(size_t), uint32_t *result)
{
        size_t n = 0;
        const char *p = string;
        const char *end = p + length;
        while (P_WITHIN_STR(p, end, use_length)) {
                n += decompose_step(u_dref(p), decompose, OFFSET_IF(result, n));
                p = u_next(p);
        }
        return n;
}

static inline bool
canonical_ordering_swap(uint32_t *string, size_t offset, int next)
{
        size_t initial = offset + 1;
        size_t j = initial;

        while (j > 0 && s_combining_class(string[j - 1]) > next) {
                uint32_t c = string[j];
                string[j] = string[j - 1];
                string[j - 1] = c;
                j--;
        }

        return j != initial;
}

static inline bool
canonical_ordering_reorder(uint32_t *string, size_t length)
{
        bool swapped = false;

        int prev = s_combining_class(string[0]);
        for (size_t i = 0; i < length - 1; i++) {
                int next = s_combining_class(string[i + 1]);

                if (next != 0 && prev > next) {
                        if (canonical_ordering_swap(string, i, next))
                                swapped = true;
                } else
                        prev = next;
        }

        return swapped;
}

static void
canonical_ordering(uint32_t *string, size_t length)
{
        while (canonical_ordering_reorder(string, length))
                ;
}

static inline bool
combine_hangul(uint32_t a, uint32_t b, uint32_t *result)
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
combine(uint32_t a, uint32_t b, uint32_t *result)
{
        if (combine_hangul(a, b, result))
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
compose_loop(uint32_t *string, size_t length)
{
        size_t n = length;
        size_t prev_start = 0;
        int prev_cc = 0;

        for (size_t i = 0; i < length; i++) {
                int cc = s_combining_class(string[i]);
                size_t j = i - (length - n);

                if (j > 0 &&
                    (prev_cc == 0 || prev_cc < cc) &&
                    combine(string[prev_start], string[i], &string[prev_start])) {
                        n--;
                        prev_cc = (j + 1 == prev_start) ?
                                0 :
                                s_combining_class(string[j - 1]);
                } else {
                        if (cc == 0)
                                prev_start = j;

                        string[j] = string[i];
                        prev_cc = cc;
                }
        }

        return n;
}

uint32_t *
_u_normalize_wc(const char *string, size_t length, bool use_length,
                enum u_normalize_mode mode, size_t *new_length)
{
        const char *(*decompose)(size_t) =
                (mode == U_NORMALIZE_NFKC || mode == U_NORMALIZE_NFKD) ?
                compatible : canonical;
        size_t n = decompose_loop(string, length, use_length, decompose, NULL);
        uint32_t *result = ALLOC_N(uint32_t, n + 1);
        decompose_loop(string, length, use_length, decompose, result);
        if (n > 0)
                canonical_ordering(result, n);

        if (mode == U_NORMALIZE_NFC || mode == U_NORMALIZE_NFKC)
                n = compose_loop(result, n);

        result[n] = '\0';

        if (new_length != NULL)
                *new_length = n;

        return result;
}

char *
u_normalize(const char *string, enum u_normalize_mode mode)
{
        uint32_t *wcs = _u_normalize_wc(string, 0, false, mode, NULL);
        char *u = u_ucs4_to_u(wcs, NULL, NULL);

        free(wcs);

        return u;
}

char *
u_normalize_n(const char *string, size_t n, enum u_normalize_mode mode,
              size_t *new_n)
{
        size_t n_wcs;
        uint32_t *wcs = _u_normalize_wc(string, n, true, mode, &n_wcs);
        char *u = u_ucs4_to_u_n(wcs, n_wcs, NULL, new_n);

        free(wcs);

        return u;
}
