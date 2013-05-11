#if __GNUC__ >= 4
#  define RB_U_NULL_TERMINATED(parameter) __attribute__((__sentinel__(parameter)))
#else
#  define RB_U_NULL_TERMINATED(parameter)
#endif

void need_at_least_n_arguments(int argc, int n);

void need_m_to_n_arguments(int argc, int m, int n);

void *_rb_u_guarded_alloc(size_t n, ...) RB_U_NULL_TERMINATED(0);

int rb_u_char_to_u(uint32_t c, char *result);

void rb_u_validate(const char *string, long length);

VALUE _rb_u_character_test(VALUE string, bool (*test)(uint32_t));

VALUE _rb_u_string_test_locale(int argc, VALUE *argv, VALUE self,
                               size_t convert(char *, size_t, const char *, size_t,
                                              const char *));

VALUE _rb_u_string_convert(VALUE self,
                           size_t convert(char *, size_t, const char *, size_t));
VALUE _rb_u_string_convert_locale(int argc, VALUE *argv, VALUE self,
                                  size_t convert(char *, size_t, const char *,
                                                 size_t, const char *),
                                  const char *lc_env);

VALUE _rb_u_string_property(VALUE self, const char *name,
                            int unknown, int property(uint32_t),
                            VALUE tosym(int));

enum u_normalization_form _rb_u_symbol_to_normalization_form(VALUE symbol);

VALUE rb_u_pattern_argument(VALUE pattern, bool quote);

long rb_u_string_index_regexp(VALUE self, const char *begin, VALUE regex, bool reverse);

#ifndef HAVE_RB_ERRINFO
#  define rb_errinfo() (ruby_errinfo)
#endif

#ifndef HAVE_RB_MEMHASH
int rb_memhash(const char *string, long length);
#endif

#ifndef RETURN_SIZED_ENUMERATOR
#  define RETURN_SIZED_ENUMERATOR(self, argc, argv, size) \
        RETURN_ENUMERATOR(self, argc, argv)
#endif

#ifndef OBJ_UNTRUSTED
#  define OBJ_UNTRUSTED(o) (false)
#endif

#ifndef OBJ_UNTRUST
#  define OBJ_UNTRUST(o) do { } while (0)
#endif

long rb_u_memsearch(const void *a, long a_n, const void *b, long b_n);

NORETURN(void rb_u_raise(VALUE exception, const char *format, ...)) PRINTF(2, 3);
NORETURN(void rb_u_raise_errno(int number, const char *format, ...)) PRINTF(2, 3);

VALUE rb_u_str_new(const char *string, long length);
VALUE rb_u_str_buf_new(long length);
