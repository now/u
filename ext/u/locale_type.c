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
enum locale
_u_locale(void)
{
        const char *locale = setlocale(LC_CTYPE, NULL);
        return locale == NULL ? LOCALE_NORMAL : _u_locale_from_string(locale);
}

enum locale
_u_locale_from_string(const char *locale)
{
        if (locale == NULL)
                return _u_locale();

        if (locale[0] == '\0')
                return LOCALE_NORMAL;

	if ((locale[0] == 'a' && locale[1] == 'z') ||
	    (locale[0] == 't' && locale[1] == 'r'))
		return LOCALE_TURKIC;

	if (locale[0] == 'l' && locale[1] == 't')
		return LOCALE_LITHUANIAN;

        if (locale[0] == 'n' && locale[1] == 'l')
                return LOCALE_DUTCH;

        return LOCALE_NORMAL;
}
