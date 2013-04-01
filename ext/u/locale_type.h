#ifndef LOCALE_TYPE_H
#define LOCALE_TYPE_H


/* {{{1
 * LocaleType: This ‹enum› is used for dealing with different locales for
 * turning strings into uppercase or lowercase.
 */
enum locale {
	LOCALE_NORMAL,
	LOCALE_TURKIC,
	LOCALE_LITHUANIAN,
        LOCALE_DUTCH,
};


HIDDEN enum locale _u_locale(void);
HIDDEN enum locale _u_locale_from_string(const char *locale);


#endif /* LOCALE_TYPE_H */
