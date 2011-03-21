/*
 * contents: Private Ruby-related functions.
 *
 * Copyright © 2007 Nikolai Weibull <now@bitwi.se>
 */

#ifndef RB_PRIVATE_H
#define RB_PRIVATE_H


void need_at_least_n_arguments(int argc, int n) HIDDEN;

void need_m_to_n_arguments(int argc, int m, int n) HIDDEN;

unichar _utf_char_validated(char const *const str,
                            char const *const str_end) HIDDEN;
char *_utf_offset_to_pointer_validated_impl(const char *str, long offset,
                                            const char *limit, bool noisy) HIDDEN;

char *_utf_offset_to_pointer_validated(const char *str, long offset,
                                       const char *end) HIDDEN;

char *_utf_offset_to_pointer_failable(const char *str, long offset,
                                      const char *end) HIDDEN;

VALUE rb_u_new(const char *str, long len) HIDDEN;

VALUE rb_u_new2(const char *str) HIDDEN;

VALUE rb_u_new5(VALUE obj, const char *str, long len) HIDDEN;

VALUE rb_u_alloc_using(char *str) HIDDEN;

VALUE rb_u_dup(VALUE str) HIDDEN;

long rb_u_index(VALUE str, VALUE sub, long offset) HIDDEN;

bool rb_u_begin_from_offset(VALUE str, long offset, char **begin,
                              char **limit) HIDDEN;

void rb_u_begin_from_offset_validated(VALUE str, long offset, char **begin,
                                        char **limit) HIDDEN;

char *rb_u_prev_validated(const char *begin, const char *p) HIDDEN;

VALUE rb_u_update(VALUE str, long offset, long len, VALUE replacement) HIDDEN;

char *rb_u_next_validated(const char *p, const char *end) HIDDEN;

long rb_u_index_regexp(VALUE str, const char *s, const char *end, VALUE sub,
                         long offset, bool reverse) HIDDEN;


#endif /* RB_PRIVATE_H */
