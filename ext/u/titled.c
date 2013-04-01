#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "data/constants.h"
#include "data/title-table.h"

#include "general-category.h"
#include "titled.h"

/* {{{1
 * Determine whether ‘c’ is a titlecase letter, such as the slavic digraph Ǳ,
 * which at the beginning of a word is written as ǲ, where only the initial D
 * is capitalized.  (Complicated huh?)
 */
bool
u_char_istitle(uint32_t c)
{
        size_t index;

        return unicode_table_lookup(title_table, c, &index);
}


/* {{{1
 * Convert ‘c’ to its titlecase representation (if any).
 */
uint32_t
u_char_totitle(uint32_t c)
{
	for (size_t i = 0; i < lengthof(title_table); i++)
                if (title_table[i].ch == c ||
                    title_table[i].upper == c ||
                    title_table[i].lower == c)
			return title_table[i].ch;

        if (s_general_category(c) == U_GENERAL_CATEGORY_LETTER_LOWERCASE)
                return u_char_toupper(c);

        return c;
}


uint32_t
_u_titlecase_table_lookup(uint32_t c, bool want_upper)
{
        size_t index;

        if (!unicode_table_lookup(title_table, c, &index))
                return c;

        return want_upper ? title_table[index].upper : title_table[index].lower;
}
