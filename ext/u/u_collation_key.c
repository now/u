#include "extconf.h"
#include <assert.h>
#include <errno.h>
#include <langinfo.h>
#include <locale.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#ifdef HAVE_XLOCALE_H
#  include <xlocale.h>
#endif
#ifndef HAVE_STRXFRM_L
static inline size_t
strxfrm_l(char *restrict s1, const char *restrict s2, size_t n,
          UNUSED(locale_t loc))
{
        return strxfrm(s1, s2, n);
}
#endif
#ifndef HAVE_NL_LANGINFO_L
static inline char *
nl_langinfo_l(nl_item item, UNUSED(locale_t loc))
{
        return nl_langinfo(item);
}
#endif

#include "u.h"
#include "private.h"

static inline const char *
codeset(locale_t locale)
{
        return locale == NULL ?
                nl_langinfo(CODESET) :
                nl_langinfo_l(CODESET, locale);
}

static inline size_t
transform(char *result, const char *string, size_t n, locale_t locale)
{
        return locale == NULL ?
                strxfrm(result, string, n) :
                strxfrm_l(result, string, n, locale);
}

static size_t
ckey(char *result, size_t m, const char *string, size_t n, locale_t locale)
{
        char saved_sentinel = string[n];
        ((char *)string)[n] = '\0';
        size_t l = 0;
        const char *p = string;
        const char *end = string + n +1;
        while (true) {
                errno = 0;
                size_t k = m > l ?
                        transform(result + l, p, m - l, locale) :
                        transform(NULL, p, 0, locale);
                if (errno != 0)
                        break;
                l += k;
                p += strlen(p) + 1;
                if (p == end)
                        break;
                if (m > l)
                        result[l] = '\0';
                l++;
        }
        ((char *)string)[n] = saved_sentinel;
        return l;
}

static size_t
recode_ckey(char *result, size_t m, const char *string, size_t n,
            locale_t locale, const char *cs)
{
        char buf[2048];
        errno = 0;
        size_t n_recoded = u_recode(buf, sizeof(buf), string, n, cs);
        if (errno != 0)
                return 0;
        if (n_recoded < sizeof(buf))
                return ckey(result, m, buf, n_recoded, locale);
        char *recoded = malloc(n_recoded + 1);
        if (recoded == NULL)
                return 0;
        u_recode(recoded, n_recoded + 1, string, n, cs);
        size_t n_key = ckey(result, m, recoded, n_recoded, locale);
        free(recoded);
        return n_key;
}

size_t
u_collation_key(char *result, size_t m, const char *string, size_t n,
                const char *locale)
{
        locale_t l = NULL;
        if (locale != NULL)
                l = newlocale(LC_COLLATE_MASK | LC_CTYPE_MASK, locale, NULL);
        const char *cs = codeset(l);
        size_t r = strcmp(cs, "UTF-8") != 0 ?
                recode_ckey(result, m, string, n, l, cs) :
                ckey(result, m, string, n, l);
        if (l != NULL)
                freelocale(l);
        return r;
}

size_t
u_normalized_collation_key(char *result, size_t m, const char *string, size_t n,
                           const char *locale)
{
        char buf[2048];
        size_t n_normalized = u_normalize(buf, sizeof(buf), string, n, U_NORMALIZATION_FORM_KC);
        if (n_normalized < sizeof(buf))
                return u_collation_key(result, m, buf, n_normalized, locale);
        char *normalized = malloc(n_normalized + 1);
        if (normalized == NULL)
                return 0;
        u_normalize(normalized, n_normalized + 1, string, n, U_NORMALIZATION_FORM_KC);
        size_t n_key = u_collation_key(result, m, normalized, n_normalized, locale);
        free(normalized);
        return n_key;
}
