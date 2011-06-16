#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "data/title-table.h"

#include "titled.h"
#include "types.h"

/* {{{1
 * Determine whether ‘c’ is a titlecase letter, such as the slavic digraph Ǳ,
 * which at the beginning of a word is written as ǲ, where only the initial D
 * is capitalized.  (Complicated huh?)
 */
bool
unichar_istitle(unichar c)
{
        int index;

        return unicode_table_lookup(title_table, c, &index);
}


/* {{{1
 * Convert ‘c’ to its titlecase representation (if any).
 */
unichar
unichar_totitle(unichar c)
{
	for (size_t i = 0; i < lengthof(title_table); i++)
                if (title_table[i].ch == c ||
                    title_table[i].upper == c ||
                    title_table[i].lower == c)
			return title_table[i].ch;

        if (s_type(c) == UNICODE_LOWERCASE_LETTER)
                return unichar_toupper(c);

        return c;
}


unichar
_u_titlecase_table_lookup(unichar c, bool want_upper)
{
        int index;

        if (!unicode_table_lookup(title_table, c, &index))
                return c;

        return want_upper ? title_table[index].upper : title_table[index].lower;
}