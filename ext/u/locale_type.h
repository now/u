#ifndef LOCALE_TYPE_H
#define LOCALE_TYPE_H


/* {{{1
 * LocaleType: This ‹enum› is used for dealing with different locales for
 * turning strings into uppercase or lowercase.
 */
typedef enum {
	LOCALE_NORMAL,
	LOCALE_TURKIC,
	LOCALE_LITHUANIAN
} LocaleType;


HIDDEN LocaleType _u_locale_type(void);
HIDDEN LocaleType _u_locale_type_from_string(const char *locale);


#endif /* LOCALE_TYPE_H */
