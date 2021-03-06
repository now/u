#include <ruby.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "u.h"

#include "private.h"

/* Lookup C in the sorted TABLE using binary search.  TABLE consists of N
 * entries, where each entry is SIZEOF_ENTRY bytes in size and the first
 * component is a uint32_t of size SIZEOF_CHAR.  If C is found in TABLE, its
 * index is stored in INDEX and true is returned.  Otherwise, false is returned
 * and INDEX is left untouched. */
bool
binary_search_unicode_table(const void *table, size_t n, size_t sizeof_entry, size_t sizeof_char, uint32_t c, size_t *index)
{
#define ENTRY(index) (*(uint32_t *)(void *)((const char *)table + ((index) * sizeof_entry)) & char_mask)

	size_t begin = 0;
        size_t end = n - 1;
        size_t middle;

        /* This is ugly, but not all tables use unichars as their lookup
         * character.  The casefold table, for example, uses uint16_t-sized
         * characters.  To only get the interesting part of our table entry
         * we’ll have to mask the retrieved value. */
        uint32_t char_mask = sizeof_char < sizeof(uint32_t) ?
                ((uint32_t)1 << (CHAR_BIT * sizeof_char)) - 1 :
                (uint32_t)-1;

        /* Drop out early if we know for certain that C can’t be in the
         * decomposition table. */
        if (c < ENTRY(0) || c > ENTRY(end))
                return false;

        while (begin <= end) {
                middle = binary_search_middle_of(begin, end);

                uint32_t probe = ENTRY(middle);
                if (c < probe)
                        end = middle - 1;
                else if (c > probe)
                        begin = middle + 1;
                else
                        break;
        }

        if (begin > end)
                return false;

        *index = middle;

        return true;

#undef ENTRY
}
