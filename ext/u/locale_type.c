#include <locale.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "u.h"
#include "private.h"

#include "locale_type.h"


/* {{{1
 * Retrieve the locale type from the environment (LC_CTYPE).
 */
LocaleType
_u_locale_type(void)
{
	const char *locale = setlocale(LC_CTYPE, NULL);

	if ((locale[0] == 'a' && locale[1] == 'z') ||
	    (locale[0] == 't' && locale[1] == 'r'))
		return LOCALE_TURKIC;

	if (locale[0] == 'l' && locale[1] == 't')
		return LOCALE_LITHUANIAN;

        return LOCALE_NORMAL;
}
