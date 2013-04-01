#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"

#include "private.h"

#include "data/script.h"


static inline enum u_script
u_char_script_bsearch(uint32_t c)
{
	int begin = 0;
        int end = lengthof(script_table) - 1;
        static int cached_middle = lengthof(script_table) / 2;
        int middle = cached_middle;

        do {
                uint32_t probe = script_table[middle].start;
                if (c < probe)
                        end = middle - 1;
                else if (c >= probe + script_table[middle].chars)
                        begin = middle + 1;
                else
                        return script_table[cached_middle = middle].script;

                middle = binary_search_middle_of(begin, end);
        } while (begin <= end);

        return U_SCRIPT_UNKNOWN;
}

enum u_script
u_char_script(uint32_t c)
{
        return c < EASY_SCRIPTS_RANGE ?
                script_easy_table[c] :
                u_char_script_bsearch(c);
}
