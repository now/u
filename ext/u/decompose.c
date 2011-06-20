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


static inline bool
unicode_canonical_ordering_swap(unichar *string, size_t offset, int next)
{
        size_t initial = offset + 1;
        size_t j = initial;

        while (j > 0 && s_combining_class(string[j - 1]) > next) {
                unichar c = string[j];
                string[j] = string[j - 1];
                string[j - 1] = c;
                j--;
        }

        return j != initial;
}

static inline bool
unicode_canonical_ordering_reorder(unichar *string, size_t length)
{
        bool swapped = false;

        int prev = s_combining_class(string[0]);
        for (size_t i = 0; i < length - 1; i++) {
                int next = s_combining_class(string[i + 1]);

                if (next != 0 && prev > next) {
                        if (unicode_canonical_ordering_swap(string, i, next))
                                swapped = true;
                } else
                        prev = next;
        }

        return swapped;
}

static void
unicode_canonical_ordering(unichar *string, size_t length)
{
        while (unicode_canonical_ordering_reorder(string, length))
                ;
}

/* Decompose the character ‘s’ according to the rules outlined in
 * http://www.unicode.org/unicode/reports/tr15/#Hangul. */
static size_t
decompose_hangul(unichar s, unichar *result)
{
        int SIndex = s - SBase;

        if (SIndex < 0 || SIndex >= SCount) {
                if (result != NULL)
                        result[0] = s;

                return 1;
        }

        unichar L = LBase + SIndex / NCount;
        unichar V = VBase + (SIndex % NCount) / TCount;
        unichar T = TBase + SIndex % TCount;

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

static inline const char *
find_decomposition(unichar c, bool compat)
{
        int index;
        if (!unicode_table_lookup(decomp_table, c, &index))
                return NULL;

        int offset;
        if (compat) {
                offset = decomp_table[index].compat_offset;
                if (offset == UNICODE_NOT_PRESENT_OFFSET)
                        offset = decomp_table[index].canon_offset;
                /* Either .compat_offset or .canon_offset can be missing, but
                 * not both. */
        } else {
                offset = decomp_table[index].canon_offset;
                if (offset == UNICODE_NOT_PRESENT_OFFSET)
                        return NULL;
        }

        return &decomp_expansion_string[offset];
}

static inline size_t
decomposition_to_wc(const char *decomposition, unichar *result)
{
        size_t i = 0;

        for (const char *p = decomposition; *p != '\0'; p = u_next(p))
                result[i++] = u_aref_char(p);

        return i;
}

static inline bool
combine_hangul(unichar a, unichar b, unichar *result)
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
compose_index(unichar c)
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
combine(unichar a, unichar b, unichar *result)
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
                unichar r = compose_array[index_a - COMPOSE_FIRST_START][index_b - COMPOSE_SECOND_START];

                if (r != 0) {
                        *result = r;

                        return true;
                }
        }

        return false;
}

static size_t
normalize_wc_decompose_one(unichar c, NormalizeMode mode, unichar *result)
{
        const char *decomposition = find_decomposition(c,
                                                       (mode == NORMALIZE_NFKC ||
                                                        mode == NORMALIZE_NFKD));

        if (decomposition == NULL) {
                if (result != NULL)
                        result[0] = c;

                return 1;
        }

        if (result != NULL)
                return decomposition_to_wc(decomposition, result);

        return u_length(decomposition);
}

static size_t
normalize_wc_decompose(const char *string, size_t length, bool use_length,
                       NormalizeMode mode, unichar *result)
{
        size_t n = 0;
        size_t prev_start = 0;

        const char *p = string;
        const char *end = p + length;
        while (P_WITHIN_STR(p, end, use_length)) {
                unichar c = u_aref_char(p);
                size_t prev_n = n;

                n += (SBase <= c && c <= SLast) ?
                        decompose_hangul(c, OFFSET_IF(result, n)) :
                        normalize_wc_decompose_one(c, mode, OFFSET_IF(result, n));

                if (result != NULL && n > 0 && s_combining_class(result[prev_n]) == 0) {
                        unicode_canonical_ordering(result + prev_start,
                                                   n - prev_start);
                        prev_start = prev_n;
                }

                p = u_next(p);
        }

        if (result != NULL && n > 0)
                unicode_canonical_ordering(result + prev_start, n - prev_start);

        return n;
}

static size_t
normalize_wc_compose(unichar *string, size_t length)
{
        int n = length;
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

unichar *
_u_normalize_wc(const char *string, size_t length, bool use_length,
                NormalizeMode mode, size_t *new_length)
{
        size_t n = normalize_wc_decompose(string, length, use_length, mode, NULL);
        unichar *result = ALLOC_N(unichar, n + 1);
        normalize_wc_decompose(string, length, use_length, mode, result);

        if (mode == NORMALIZE_NFC || mode == NORMALIZE_NFKC)
                n = normalize_wc_compose(result, n);

        result[n] = '\0';

        if (new_length != NULL)
                *new_length = n;

        return result;
}

char *
u_normalize(const char *string, NormalizeMode mode)
{
        unichar *wcs = _u_normalize_wc(string, 0, false, mode, NULL);
        char *u = ucs4_to_u(wcs, NULL, NULL);

        free(wcs);

        return u;
}

char *
u_normalize_n(const char *string, size_t length, NormalizeMode mode,
              size_t *new_length)
{
        size_t length_wcs;
        unichar *wcs = _u_normalize_wc(string, length, true, mode, &length_wcs);
        char *u = ucs4_to_u_n(wcs, length_wcs, NULL, new_length);

        free(wcs);

        return u;
}
