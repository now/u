void need_at_least_n_arguments(int argc, int n);

void need_m_to_n_arguments(int argc, int m, int n);

uint32_t _rb_u_dref(const char *str, const char *end);

char *rb_u_prev_validated(const char *begin, const char *p);

char *rb_u_next_validated(const char *p, const char *end);

int rb_u_char_to_u(uint32_t c, char *result);

void rb_u_validate(const char *string, long length);

VALUE _rb_u_character_test(VALUE string, bool (*test)(uint32_t));

VALUE _rb_u_string_test(VALUE self,
                        char *(convert)(const char *, size_t, size_t *));

VALUE _rb_u_string_test_in_locale(int argc, VALUE *argv, VALUE self,
                                  char *(convert)(const char *, size_t,
                                                  const char *, size_t *));

VALUE _rb_u_string_case_in_locale(int argc, VALUE *argv, VALUE self,
                                  char *(case_in_locale_n)(const char *,
                                                           size_t,
                                                           const char *,
                                                           size_t *));

VALUE _rb_u_string_property(VALUE self, const char *name,
                            int unknown, int property(uint32_t),
                            VALUE tosym(int));

VALUE rb_u_pattern_argument(VALUE pattern, bool quote);

long rb_u_string_index_regexp(VALUE self, const char *begin, VALUE regex, bool reverse);

#ifndef HAVE_RB_MEMHASH
int rb_memhash(const char *string, long length);
#endif

#ifndef RETURN_SIZED_ENUMERATOR
#  define RETURN_SIZED_ENUMERATOR(self, argc, argv, size) \
        RETURN_ENUMERATOR(self, argc, argv)
#endif

long rb_u_memsearch(const void *a, long a_n, const void *b, long b_n);

NORETURN(void rb_u_raise(VALUE exception, const char *format, ...)) PRINTF(2, 3);
NORETURN(void rb_u_raise_errno(VALUE exception, int number, const char *format, ...)) PRINTF(3, 4);

VALUE rb_u_str_new(const char *string, long length);
VALUE rb_u_str_buf_new(long length);
