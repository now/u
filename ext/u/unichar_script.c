#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"

#include "private.h"

#include "data/script.h"


static inline UnicodeScript
unichar_script_bsearch(unichar c)
{
	int begin = 0;
        int end = lengthof(script_table) - 1;
        static int cached_middle = lengthof(script_table) / 2;
        int middle = cached_middle;

        do {
                unichar probe = script_table[middle].start;
                if (c < probe)
                        end = middle - 1;
                else if (c >= probe + script_table[middle].chars)
                        begin = middle + 1;
                else
                        return script_table[cached_middle = middle].script;

                middle = binary_search_middle_of(begin, end);
        } while (begin <= end);

        return UNICODE_SCRIPT_UNKNOWN;
}

UnicodeScript
unichar_script(unichar c)
{
        return c < EASY_SCRIPTS_RANGE ?
                script_easy_table[c] :
                unichar_script_bsearch(c);
}