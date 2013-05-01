#define IS(category, class) (((unsigned int)1 << (category)) & (class))
#define OR(class, rest) (((unsigned int)1 << (class)) | (rest))

#define P_WITHIN_STR(p, end, use_end) \
        ((use_end) ? (p) < (end) : *(p) != '\0')

#define OFFSET_IF(buf, len) \
        (((buf) != NULL) ? (buf) + (len) : NULL)

#define lengthof(ary)   (sizeof(ary) / sizeof((ary)[0]))

#if defined(_WIN32) || defined(__CYGWIN__)
#  ifdef U_COMPILATION
#    define U_EXTERN __declspec(dllexport) extern
#  else
#    define U_EXTERN __declspec(dllimport) extern
#  endif
#elif __GNUC__ >= 4
#  define U_EXTERN __attribute__((visibility("default"))) extern
#else
#  define U_EXTERN extern
#endif

#if defined(__GNUC__) && __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ > 4)
#  define PRINTF(format_index, first_argument_index) \
        __attribute__((format(printf, format_index, first_argument_index)))
#  define UNUSED(u) \
        __attribute__((__unused__)) u
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

bool binary_search_unicode_table(const void *table,
                                 size_t n,
                                 size_t sizeof_entry,
                                 size_t sizeof_char,
                                 uint32_t c,
                                 size_t *index);

uint32_t *_u_normalize_wc(const char *string,
                          size_t n,
                          bool use_n,
                          enum u_normalize_mode mode,
                          size_t *new_n);
