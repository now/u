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
        return _u_locale_type_from_string(setlocale(LC_CTYPE, NULL));
}

LocaleType
_u_locale_type_from_string(const char *locale)
{
        if (locale == NULL)
                return _u_locale_type();

        if (locale[0] == '\0')
                return LOCALE_NORMAL;

	if ((locale[0] == 'a' && locale[1] == 'z') ||
	    (locale[0] == 't' && locale[1] == 'r'))
		return LOCALE_TURKIC;

	if (locale[0] == 'l' && locale[1] == 't')
		return LOCALE_LITHUANIAN;

        return LOCALE_NORMAL;
}
