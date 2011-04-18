#include "rb_includes.h"
#include "rb_u_string_internal_tr.h"

struct tr_range
{
        unichar begin;
        unichar end;
};

static int
tr_ranges_setup(struct tr *tr, struct tr_range *ranges)
{
        int n = 0;
        bool was_inside_range = false;
        while (tr_next(tr) != TR_FINISHED) {
                if (tr->inside_range) {
                        if (!was_inside_range) {
                                ranges[n].begin = tr->now;
                                was_inside_range = true;
                        }
                } else {
                        if (was_inside_range)
                                ranges[n].end = tr->now;
                        else
                                ranges[n].begin = ranges[n].end = tr->now;
                        n++;
                        was_inside_range = false;
                }
        }

        return n;
}


struct tr_trans_closure
{
        struct tr_range *from;
        int n_from;
        struct tr_range *to;
        int n_to;
};

static unichar
tr_trans_replace_exclude(UNUSED(unichar c), void *closure)
{
        return *((unichar *)closure);
}

static int
tr_trans_replace_include_offset_of(struct tr_range *ranges, int range, unichar c)
{
        int offset = 0;

        for (int i = 0; i < range; i++)
                offset += ranges[i].end - ranges[i].begin + 1;
        offset += c - ranges[range].begin;

        return offset;
}

static int
tr_trans_replace_include_find_from_range(struct tr_trans_closure *closure, unichar c)
{
        for (int i = closure->n_from - 1; i >= 0; i--)
                if (closure->from[i].begin <= c && c <= closure->from[i].end)
                        return i;

        return -1;
}

static unichar
tr_trans_replace_include_find_to_unichar(struct tr_trans_closure *closure, int offset)
{
        for (int i = 0, seen = 0; i < closure->n_to; i++) {
                int size = closure->to[i].end - closure->to[i].begin + 1;
                if (seen + size > offset)
                        return closure->to[i].begin + (offset - seen);
                seen += size;
        }

        return closure->to[closure->n_to - 1].end;
}

static unichar
tr_trans_replace_include(unichar c, void *v_closure)
{
        struct tr_trans_closure *closure = (struct tr_trans_closure *)v_closure;

        int from = tr_trans_replace_include_find_from_range(closure, c);
        if (from == -1)
                return closure->to[closure->n_to - 1].end;

        int offset = tr_trans_replace_include_offset_of(closure->from, from, c);

        return tr_trans_replace_include_find_to_unichar(closure, offset);
}

static long
tr_trans_real_squeeze(const char *str, const char *end,
                      struct tr_table *translation,
                      unichar (*replace)(unichar, void *), void *closure,
                      char *result, bool *modified)
{
        long len = 0;

        const char *p = str;

        unichar prev_c = UNICODE_N_CODEPOINTS;
        while (p < end) {
                unichar c0 = u_aref_char(p);

                const char *prev = p;
                p = u_next(p);

                if (tr_table_lookup(translation, c0)) {
                        unichar c = replace(c0, closure);
                        if (prev_c == c)
                                continue;
                        prev_c = c;
                        len += unichar_to_u(c, OFFSET_IF(result, len));
                        if (c != c0)
                                *modified = true;
                } else {
                        long run = p - prev;
                        if (result != NULL)
                                memcpy(result + len, prev, run);
                        len += run;

                        prev_c = UNICODE_N_CODEPOINTS;
                }

        }

        if (end - str > len)
                *modified = true;

        return len;
}

static long
tr_trans_real_standard(const char *str, const char *end,
                       struct tr_table *translation,
                       unichar (*replace)(unichar, void *), void *closure,
                       char *result, bool *modified)
{
        long len = 0;

        const char *p = str;

        while (p < end) {
                unichar c = u_aref_char(p);

                const char *prev = p;
                p = u_next(p);

                if (tr_table_lookup(translation, c)) {
                        unichar replacement = replace(c, closure);
                        len += unichar_to_u(replacement, OFFSET_IF(result, len));
                        if (replacement != c)
                                *modified = true;
                } else {
                        long run = p - prev;
                        if (result != NULL)
                                memcpy(result + len, prev, run);
                        len += run;
                }
        }

        return len;
}

static long
tr_trans_real(const char *str, const char *end,
              struct tr_table *translation,
              unichar (*replace)(unichar, void *), void *closure, bool squeeze,
              char *result, bool *modified)
{
        if (squeeze)
                return tr_trans_real_squeeze(str, end,
                                             translation,
                                             replace, closure,
                                             result, modified);
        else
                return tr_trans_real_standard(str, end,
                                              translation,
                                              replace, closure,
                                              result, modified);
}


static VALUE
tr_trans_do(VALUE self, struct tr_table *translation,
            unichar (*replace)(unichar, void *), void *closure, bool squeeze)
{
        const UString *string = RVAL2USTRING(self);

        const char *begin = USTRING_STR(string);
        const char *end = USTRING_END(string);
        bool modified = false;
        long len = tr_trans_real(begin, end,
                                 translation,
                                 replace, closure, squeeze,
                                 NULL, &modified);
        if (!modified)
                return self;
        char *result = ALLOC_N(char, len + 1);
        tr_trans_real(begin, end,
                      translation,
                      replace, closure, squeeze,
                      result, &modified);
        result[len] = '\0';

        return rb_u_string_new_own(result, len);
}

static VALUE
tr_trans(VALUE self, VALUE rbfrom, VALUE rbto, bool squeeze)
{
        const UString *string = RVAL2USTRING(self);
        const UString *from = RVAL2USTRING_ANY(rbfrom);
        const UString *to = RVAL2USTRING_ANY(rbto);

        if (USTRING_STR(string) == NULL || USTRING_LENGTH(string) == 0)
                return self;

        if (USTRING_LENGTH(to) == 0)
                return rb_u_string_delete(1, &rbfrom, self);

        struct tr tr_from;
        tr_init(&tr_from, USTRING_STR(from), USTRING_END(from));

        struct tr tr_to;
        tr_init(&tr_to, USTRING_STR(to), USTRING_END(to));

        struct tr_table translation;
        tr_table_initialize(&translation, rbfrom);

        if (tr_should_exclude(&tr_from)) {
                /* This case is easy.  Just include everything by default and
                 * exclude the rest as always.  Replace characters found by the
                 * last character found in tr_to. */
                while (tr_next(&tr_to) != TR_FINISHED)
                       ; /* We just need the last replacement character. */
                return tr_trans_do(self, &translation, tr_trans_replace_exclude,
                                   &tr_to.now, squeeze);
        }

        /* This case is hard.  We need a full-fledged lookup of what character
         * to translate to, not simply a check whether to include it or not. */
        struct tr_trans_closure trans_closure;

        struct tr_range from_ranges[u_length_n(USTRING_STR(from), USTRING_LENGTH(from))];
        trans_closure.from = from_ranges;
        trans_closure.n_from = tr_ranges_setup(&tr_from, from_ranges);

        struct tr_range to_ranges[u_length_n(USTRING_STR(to), USTRING_LENGTH(to))];
        trans_closure.to = to_ranges;
        trans_closure.n_to = tr_ranges_setup(&tr_to, to_ranges);

        return tr_trans_do(self, &translation, tr_trans_replace_include,
                           &trans_closure, squeeze);
}

VALUE
rb_u_string_tr(VALUE self, VALUE from, VALUE to)
{
        return tr_trans(self, from, to, false);
}

VALUE
rb_u_string_tr_s(VALUE self, VALUE from, VALUE to)
{
        return tr_trans(self, from, to, true);
}
