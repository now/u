#ifndef PRIVATE_H
#define PRIVATE_H

#define P_WITHIN_STR(p, end, use_end) \
        ((use_end) ? (p) < (end) : *(p) != '\0')

#define OFFSET_IF(buf, len) \
        (((buf) != NULL) ? (buf) + (len) : NULL)

#define lengthof(ary)   (sizeof(ary) / sizeof((ary)[0]))

#if defined(HAVE_GNUC_VISIBILITY)
#  define HIDDEN   \
        __attribute__((visibility("hidden")))
#else
#  define HIDDEN
#endif

#if defined(__GNUC__) && __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ > 4)
#  define PRINTF(format_index, first_argument_index) \
        __attribute__((format(printf, format_index, first_argument_index)))
#  define UNUSED(u) \
        u __attribute__((__unused__))
#else
#  define PRINTF(format, arguments)
#  define UNUSED(u) u
#endif

#if defined(__GNUC__) && __GNUC__ > 2 && defined(__OPTIMIZE__)
#  define BOOLEAN_EXPR(expr) __extension__({ \
        int _boolean_var_; \
        if (expr) \
                _boolean_var_ = 1; \
        else \
                _boolean_var_ = 0; \
        _boolean_var_; \
})
#  define LIKELY(expr) (__builtin_expect(BOOLEAN_EXPR(expr), 1))
#  define UNLIKELY(expr) (__builtin_expect(BOOLEAN_EXPR(expr), 0))
#else
#  define LIKELY(expr) (expr)
#  define UNLIKELY(expr) (expr)
#endif

#define binary_search_middle_of(begin, end)     \
        (((unsigned)((begin) + (end))) >> 1)

#define unicode_table_lookup(table, c, index)    \
        binary_search_unicode_table(table, lengthof(table), sizeof((table)[0]), sizeof((table)[0].ch), c, index)

HIDDEN bool binary_search_unicode_table(const void *table,
                                        size_t n,
                                        size_t sizeof_entry,
                                        size_t sizeof_char,
                                        uint32_t c,
                                        size_t *index);

HIDDEN uint32_t *_u_normalize_wc(const char *string,
                               size_t length,
                               bool use_length,
                               UnicodeNormalizeMode mode,
                               size_t *new_length);

#include "locale_type.h"

HIDDEN size_t _u_downcase_step(const char *string, const char *p,
                               const char *end, bool use_end,
                               LocaleType locale_type, char *result);

HIDDEN size_t _u_upcase_step(const char *string, const char **p,
                             const char *end, bool use_end,
                             LocaleType locale_type, bool title, char *result);

#endif /* PRIVATE_H */
