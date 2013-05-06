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

static inline uint32_t
decode(uint32_t *state, uint32_t *c, uint32_t b)
{
        uint32_t type = dfa[b];
        *c = *state != ACCEPT ? (*c << 6) | (b & 0x3f) : (0xff >> type) & b;
        *state = dfa[256 + *state + type];
        return *state;
}

uint32_t
u_dref(const char *u)
{
        uint32_t c, state = ACCEPT;
        for (const unsigned char *p = (const unsigned char *)u; *p != '\0'; p++)
                switch (decode(&state, &c, *p)) {
                case ACCEPT:
                        return c;
                case REJECT:
                        return U_BAD_INPUT_CHAR;
                }
        return *u == '\0' ? '\0' : U_INCOMPLETE_INPUT_CHAR;
}

uint32_t
u_dref_n(const char *u, size_t n)
{
        if (n == 0)
                return U_INCOMPLETE_INPUT_CHAR;

        uint32_t c, state = ACCEPT;
        const unsigned char *end = (const unsigned char *)u + n;
        for (const unsigned char *p = (const unsigned char *)u; p < end; p++)
                switch (decode(&state, &c, *p)) {
                case ACCEPT:
                        return c;
                case REJECT:
                        return *p == '\0' ? U_INCOMPLETE_INPUT_CHAR : U_BAD_INPUT_CHAR;
                }
        return U_INCOMPLETE_INPUT_CHAR;
}

static inline uint32_t
validate(uint32_t c)
{
	if (c & 0x80000000)
		return c;
	else if (!u_char_isvalid(c))
		return U_BAD_INPUT_CHAR;
	else
		return c;
}

uint32_t
u_dref_validated(const char *u)
{
	return validate(u_dref(u));
}

uint32_t
u_dref_validated_n(const char *u, size_t n)
{
	return validate(u_dref_n(u, n));
}
