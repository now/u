#ifndef RB_PRIVATE_H
#define RB_PRIVATE_H

HIDDEN void need_at_least_n_arguments(int argc, int n);

HIDDEN void need_m_to_n_arguments(int argc, int m, int n);

HIDDEN uint32_t _rb_u_aref_char_validated(const char *str, const char *end);

HIDDEN char *rb_u_prev_validated(const char *begin, const char *p);

HIDDEN char *rb_u_next_validated(const char *p, const char *end);

HIDDEN int rb_u_char_to_u(uint32_t c, char *result);

HIDDEN void rb_u_validate(const char *string, long length);

HIDDEN VALUE _rb_u_character_test(VALUE string, bool (*test)(uint32_t));

HIDDEN VALUE _rb_u_string_test(VALUE self,
                               char *(convert)(const char *, size_t, size_t *));

HIDDEN VALUE _rb_u_string_test_in_locale(int argc, VALUE *argv, VALUE self,
                                         char *(convert)(const char *, size_t,
                                                         const char *, size_t *));

HIDDEN VALUE _rb_u_string_case_in_locale(int argc, VALUE *argv, VALUE self,
                                         char *(case_in_locale_n)(const char *,
                                                                  size_t,
                                                                  const char *,
                                                                  size_t *));

HIDDEN VALUE _rb_u_string_property(VALUE self, const char *name,
                                   int unknown, int property(uint32_t),
                                   VALUE tosym(int));

HIDDEN VALUE rb_u_pattern_argument(VALUE pattern, bool quote);

HIDDEN long rb_u_string_index_regexp(VALUE self, const char *begin, VALUE regex, bool reverse);

#ifndef HAVE_RB_MEMHASH
HIDDEN int rb_memhash(const char *string, long length);
#endif

HIDDEN long rb_u_memsearch(const void *a, long a_n, const void *b, long b_n);

HIDDEN NORETURN(void rb_u_raise(VALUE exception, const char *format, ...)) PRINTF(2, 3);

HIDDEN VALUE rb_u_str_new(const char *string, long length);
HIDDEN VALUE rb_u_str_buf_new(long length);

#endif /* RB_PRIVATE_H */
