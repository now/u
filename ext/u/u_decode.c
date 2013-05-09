#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "u.h"
#include "private.h"


// The dfa table and decode function is © 2008–2010 Björn Höhrmann
// <bjoern@hoehrmann.de>.  See http://bjoern.hoehrmann.de/utf-8/decoder/dfa/
// for details.

enum {
        ACCEPT = 0,
        REJECT = 12
};

static const uint8_t dfa[] = {
        // The first part of the table maps bytes to character classes to
        // reduce the size of the transition table and create bitmasks.
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
        7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
        8,8,2,2,2,2,2,2,2,2,2,2,2,2,2,2,  2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
       10,3,3,3,3,3,3,3,3,3,3,3,3,4,3,3, 11,6,6,6,5,8,8,8,8,8,8,8,8,8,8,8,

        // The second part is a transition table that maps a combination
        // of a state of the automaton and a character class to a state.
        0,12,24,36,60,96,84,12,12,12,48,72, 12,12,12,12,12,12,12,12,12,12,12,12,
       12, 0,12,12,12,12,12, 0,12, 0,12,12, 12,24,12,12,12,12,12,24,12,24,12,12,
       12,12,12,12,12,12,12,24,12,12,12,12, 12,24,12,12,12,12,12,12,12,24,12,12,
       12,12,12,12,12,12,12,36,12,36,12,12, 12,36,12,12,12,12,12,36,12,36,12,12,
       12,36,12,12,12,12,12,12,12,12,12,12,
};

// This reversal of ‹dfa› is © 2013 Nikolai Weibull.
static const uint8_t dfa_r[] = {
        // The first part of the table maps bytes to character classes to
        // reduce the size of the transition table and create bitmasks.
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,  9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
        7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
        8,8,2,2,2,2,2,2,2,2,2,2,2,2,2,2,  2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
       10,3,3,3,3,3,3,3,3,3,3,3,3,4,3,3, 11,6,6,6,5,8,8,8,8,8,8,8,8,8,8,8,

        // The second part is a transition table that maps a combination
        // of a state of the automaton and a character class to a state.
        0,24,12,12,12,12,12,24,12,24,12,12, 12,12,12,12,12,12,12,12,12,12,12,12,
       12,36, 0,12,12,12,12,48,12,36,12,12, 12,60,12, 0, 0,12,12,72,12,72,12,12,
       12,60,12, 0,12,12,12,72,12,72, 0,12, 12,12,12,12,12, 0, 0,12,12,12,12,12,
       12,12,12,12,12,12, 0,12,12,12,12, 0,
};

static inline uint32_t
decode(uint32_t *state, uint32_t *c, uint32_t b)
{
        uint32_t type = dfa[b];
        *c = *state != ACCEPT ? (*c << 6) | (b & 0x3f) : (0xff >> type) & b;
        *state = dfa[256 + *state + type];
        return *state;
}

#define REPLACEMENT_CHARACTER ((uint32_t)0xfffd)

uint32_t
u_decode(const char **q, const char *u, const char *end)
{
        assert(u < end);
        uint32_t c, state = ACCEPT;
        const unsigned char *p;
        for (p = (const unsigned char *)u; p < (const unsigned char *)end; p++)
                switch (decode(&state, &c, *p)) {
                case ACCEPT:
                        *q = (const char *)p + 1;
                        return c;
                case REJECT:
                        *q = (const char *)p + 1;
                        return REPLACEMENT_CHARACTER;
                }
        *q = (const char *)p;
        return REPLACEMENT_CHARACTER;
}

int
u_decode_n(uint32_t *result, const char *u, size_t n)
{
        const char *q;
        *result = u_decode(&q, u, u + n);
        return (int)(q - u);
}

static inline uint32_t
decode_r(uint32_t *state, uint32_t *c, uint32_t b, int i)
{
        uint32_t type = dfa_r[b];
        *state = dfa_r[256 + *state + type];
        *c |= (*state != ACCEPT ? b & 0x3f : (0xff >> type) & b) << (6*i);
        return *state;
}

uint32_t
u_decode_r(const char **p, const char *begin, const char *u)
{
        assert(begin < u);
        uint32_t c = 0, state = ACCEPT;
        int i = 0;
        const unsigned char *q;
        for (q = (const unsigned char *)u - 1; (const unsigned char *)begin <= q; q--, i++)
                switch (decode_r(&state, &c, *q, i)) {
                case ACCEPT:
                        *p = (const char *)q;
                        return c;
                case REJECT:
                        *p = (const char *)q;
                        return REPLACEMENT_CHARACTER;
                }
        *p = (const char *)begin;
        return REPLACEMENT_CHARACTER;
}
