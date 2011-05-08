/*
 * contents: Private Ruby-related functions.
 *
 * Copyright © 2007 Nikolai Weibull <now@bitwi.se>
 */

#ifndef RB_PRIVATE_H
#define RB_PRIVATE_H

void need_at_least_n_arguments(int argc, int n) HIDDEN;

void need_m_to_n_arguments(int argc, int m, int n) HIDDEN;

unichar _rb_u_aref_char_validated(const char *str, const char *end) HIDDEN;

char *rb_u_prev_validated(const char *begin, const char *p) HIDDEN;

char *rb_u_next_validated(const char *p, const char *end) HIDDEN;

void rb_u_validate(const char *string, long length) HIDDEN;

long rb_u_string_index_regexp(VALUE self, const char *begin, VALUE regex, bool reverse) HIDDEN;

#endif /* RB_PRIVATE_H */
