#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "u.h"

#include "data/constants.h"
#include "data/decompose.h"
#include "data/compose.h"
#include "private.h"

#include <string.h>
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

static const char *
compatible(size_t i)
{
        uint16_t j = decomp_table[i].compat_offset;
        return &decomp_expansion_string[j == UNICODE_NOT_PRESENT_OFFSET ?
                                        decomp_table[i].canon_offset :
                                        j];
}

static const char *
canonical(size_t i)
{
        uint16_t j = decomp_table[i].canon_offset;
        return j == UNICODE_NOT_PRESENT_OFFSET ? NULL : &decomp_expansion_string[j];
}

static void
decompose(const char *u, const char *end, enum u_normalization_form form,
          struct output *o)
{
        const char *(*decompose)(size_t) =
                (form == U_NORMALIZATION_FORM_KC ||
                 form == U_NORMALIZATION_FORM_KD) ? compatible : canonical;
        for (const char *p = u; p < end; ) {
                uint32_t c = u_decode(&p, p, end);
                if (SBase <= c && c <= SLast) {
                        int SIndex = c - SBase;
                        output_char(o, LBase + SIndex / NCount);
                        output_char(o, VBase + (SIndex % NCount) / TCount);
                        uint32_t T = TBase + SIndex % TCount;
                        if (T != TBase)
                                output_char(o, T);
                } else {
                        size_t i;
                        const char *d;
                        if (unicode_table_lookup(decomp_table, c, &i) &&
                            (d = decompose(i)) != NULL)
                                output_zstring(o, d);
                        else
                                output_char(o, c);
                }
        }
}

static inline void
canonical_swap(char *begin, char *p, char *q,
               enum u_canonical_combining_class ccc)
{
        char *r = p;
        char *s;
        while (begin < r &&
               u_char_canonical_combining_class(u_decode_r((const char **)&s,
                                                           begin, r)) > ccc)
                r = s;
        char buf[U_CHAR_MAX_BYTE_LENGTH];
        size_t n = q - p;
        memcpy(buf, p, n);
        memmove(r + n, r, p - r);
        memcpy(r, buf, n);
}

static inline bool
canonical_reorder(char *begin, char *end)
{
        bool swapped = false;
        char *p;
        uint32_t c = u_decode((const char **)&p, begin, end);
        enum u_canonical_combining_class pcc = u_char_canonical_combining_class(c);
        while (p < end) {
                char *q;
                enum u_canonical_combining_class cc =
                        u_char_canonical_combining_class(u_decode((const char **)&q, p, end));
                if (cc != 0 && pcc > cc) {
                        canonical_swap(begin, p, q, cc);
                        swapped = true;
                } else
                        pcc = cc;
                p = q;
        }
        return swapped;
}

static void
canonical_order(char *begin, size_t n)
{
        char *end = begin + n;
        while (canonical_reorder(begin, end))
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
        int16_t i = compose_table[page];
        if (i >= UNICODE_MAX_TABLE_INDEX)
                return i - UNICODE_MAX_TABLE_INDEX;
        return compose_data[i][c & 0xff];
}

static inline bool
compose_2(uint32_t a, uint32_t b, uint32_t *result)
{
        if (compose_hangul(a, b, result))
                return true;

        uint16_t i = compose_index(a);
        if (COMPOSE_FIRST_SINGLE_START <= i && i < COMPOSE_SECOND_START) {
                if (b != compose_first_single[i - COMPOSE_FIRST_SINGLE_START][0])
                        return false;
                *result = compose_first_single[i - COMPOSE_FIRST_SINGLE_START][1];
                return true;
        }

        uint16_t j = compose_index(b);
        if (COMPOSE_SECOND_SINGLE_START <= j) {
                if (a != compose_second_single[j - COMPOSE_SECOND_SINGLE_START][0])
                        return false;
                *result = compose_second_single[j - COMPOSE_SECOND_SINGLE_START][1];
                return true;
        }

        if (COMPOSE_FIRST_START <= i && i < COMPOSE_FIRST_SINGLE_START &&
            COMPOSE_SECOND_START <= j && j < COMPOSE_SECOND_SINGLE_START) {
                uint32_t r = compose_array[i - COMPOSE_FIRST_START][j - COMPOSE_SECOND_START];
                if (r != 0) {
                        *result = r;
                        return true;
                }
        }

        return false;
}

static inline size_t
compose(char *begin, size_t n, enum u_normalization_form form)
{
        if (form != U_NORMALIZATION_FORM_C && form != U_NORMALIZATION_FORM_KC)
                return n;
        int pcc = -1;
        char *t;
        char *s = begin;
        char *end = begin + n;
        uint32_t sc = u_decode((const char **)&t, s, end);
        for (char *p = t, *q; p < end; p = q) {
                uint32_t c = u_decode((const char **)&q, p, end);
                int cc = u_char_canonical_combining_class(c);
                uint32_t sc2;
                if (pcc < cc && compose_2(sc, c, &sc2)) {
                        char *r = u_next(s);
                        ptrdiff_t k = u_char_to_u(sc2, NULL) - (r - s);
                        memmove(r + k, r, t - r);
                        u_char_to_u(sc2, s);
                        sc = sc2;
                        t += k;
                } else if (cc == 0) {
                        pcc = -1;
                        s = t;
                        sc = c;
                        t += u_char_to_u(c, t);
                } else {
                        pcc = cc;
                        t += u_char_to_u(c, t);
                }
        }
        return t - begin;
}

size_t
u_normalize(char *result, size_t m, const char *u, size_t n,
            enum u_normalization_form form)
{
        struct output o = OUTPUT_INIT(result, m);
        decompose(u, u + n, form, &o);
        if (o.m > o.n && o.n > 0) {
                canonical_order(o.result, o.n);
                o.n = compose(o.result, o.n, form);
        }
        return output_finalize(&o);
}
