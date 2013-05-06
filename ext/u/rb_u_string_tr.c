#include "rb_includes.h"
#include "rb_u_string_internal_tr.h"

#include "output.h"

struct tr_range
{
        uint32_t begin;
        uint32_t end;
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

static uint32_t
tr_trans_replace_exclude(UNUSED(uint32_t c), void *closure)
{
        return *((uint32_t *)closure);
}

static int
tr_trans_replace_include_offset_of(struct tr_range *ranges, int range, uint32_t c)
{
        int offset = 0;

        for (int i = 0; i < range; i++)
                offset += ranges[i].end - ranges[i].begin + 1;
        offset += c - ranges[range].begin;

        return offset;
}

static int
tr_trans_replace_include_find_from_range(struct tr_trans_closure *closure, uint32_t c)
{
        for (int i = closure->n_from - 1; i >= 0; i--)
                if (closure->from[i].begin <= c && c <= closure->from[i].end)
                        return i;

        return -1;
}

static uint32_t
tr_trans_replace_include_find_to_u_char(struct tr_trans_closure *closure, int offset)
{
        for (int i = 0, seen = 0; i < closure->n_to; i++) {
                int size = closure->to[i].end - closure->to[i].begin + 1;
                if (seen + size > offset)
                        return closure->to[i].begin + (offset - seen);
                seen += size;
        }

        return closure->to[closure->n_to - 1].end;
}

static uint32_t
tr_trans_replace_include(uint32_t c, void *v_closure)
{
        struct tr_trans_closure *closure = (struct tr_trans_closure *)v_closure;

        int from = tr_trans_replace_include_find_from_range(closure, c);
        if (from == -1)
                return closure->to[closure->n_to - 1].end;

        int offset = tr_trans_replace_include_offset_of(closure->from, from, c);

        return tr_trans_replace_include_find_to_u_char(closure, offset);
}

static void
tr_trans_real_squeeze(const char *str, const char *end,
                      struct tr_table *translation,
                      uint32_t replace(uint32_t, void *), void *closure,
                      struct output *output, bool *modified)
{
        size_t n = output->n;
        const char *p = str;
        uint32_t prev_c = U_N_CODEPOINTS;
        while (p < end) {
                uint32_t c0 = u_dref(p);
                const char *prev = p;
                p = u_next(p);
                if (tr_table_lookup(translation, c0)) {
                        uint32_t c = replace(c0, closure);
                        if (prev_c == c)
                                continue;
                        prev_c = c;
                        output_char(output, c);
                        if (c != c0)
                                *modified = true;
                } else {
                        output_string(output, prev, p - prev);
                        prev_c = U_N_CODEPOINTS;
                }
        }

        if ((size_t)(end - str) > (output->n - n))
                *modified = true;
}

static void
tr_trans_real_standard(const char *str, const char *end,
                       struct tr_table *translation,
                       uint32_t replace(uint32_t, void *), void *closure,
                       struct output *output, bool *modified)
{
        const char *p = str;

        while (p < end) {
                uint32_t c = u_dref(p);
                const char *prev = p;
                p = u_next(p);
                if (tr_table_lookup(translation, c)) {
                        uint32_t replacement = replace(c, closure);
                        output_char(output, replacement);
                        if (replacement != c)
                                *modified = true;
                } else
                        output_string(output, prev, p - prev);
        }
}

static void
tr_trans_real(const char *str, const char *end,
              struct tr_table *translation,
              uint32_t replace(uint32_t, void *), void *closure, bool squeeze,
              struct output *output, bool *modified)
{
        if (squeeze)
                tr_trans_real_squeeze(str, end,
                                      translation,
                                      replace, closure,
                                      output, modified);
        else
                tr_trans_real_standard(str, end,
                                       translation,
                                       replace, closure,
                                       output, modified);
}

static VALUE
tr_trans_do(VALUE self, struct tr_table *translation,
            uint32_t (*replace)(uint32_t, void *), void *closure, bool squeeze)
{
        const struct rb_u_string *string = RVAL2USTRING(self);

        const char *begin = USTRING_STR(string);
        const char *end = USTRING_END(string);
        bool modified = false;
        struct output output = OUTPUT_INIT(NULL, 0);
        tr_trans_real(begin, end,
                      translation,
                      replace, closure, squeeze,
                      &output, &modified);
        if (!modified)
                return self;
        output.result = ALLOC_N(char, output.n + 1);
        output.m = output.n + 1;
        output.n = 0;
        tr_trans_real(begin, end,
                      translation,
                      replace, closure, squeeze,
                      &output, &modified);
        output_finalize(&output);

        return rb_u_string_new_c_own(self, output.result, output.n);
}

static VALUE
tr_trans(VALUE self, VALUE rbfrom, VALUE rbto, bool squeeze)
{
        const struct rb_u_string *string = RVAL2USTRING(self);
        const struct rb_u_string *from = RVAL2USTRING_ANY(rbfrom);
        const struct rb_u_string *to = RVAL2USTRING_ANY(rbto);

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

        struct tr_range from_ranges[u_n_chars_n(USTRING_STR(from), USTRING_LENGTH(from))];
        trans_closure.from = from_ranges;
        trans_closure.n_from = tr_ranges_setup(&tr_from, from_ranges);

        struct tr_range to_ranges[u_n_chars_n(USTRING_STR(to), USTRING_LENGTH(to))];
        trans_closure.to = to_ranges;
        trans_closure.n_to = tr_ranges_setup(&tr_to, to_ranges);

        return tr_trans_do(self, &translation, tr_trans_replace_include,
                           &trans_closure, squeeze);
}

/* @overload tr(from, to)
 *
 *   Returns the receiver, translating characters in FROM to their equivalent
 *   character, by index, in TO, inheriting any taint and untrust.  If
 *   TO{#length} < FROM{#length}, TO[-1] will be used for any index _i_ >
 *   TO{#length}.
 *
 *   The complement of all Unicode characters and a given set of characters may
 *   be specified by prefixing a non-empty set with ‘`^`’ (U+005E CIRCUMFLEX
 *   ACCENT).
 *
 *   Any sequence of characters _a_-_b_ inside a set will expand to also
 *   include all characters whose code points lay between those of _a_ and _b_.
 *
 *   @param [#to_str] from
 *   @param [#to_str] to
 *   @return [U::String] */
VALUE
rb_u_string_tr(VALUE self, VALUE from, VALUE to)
{
        return tr_trans(self, from, to, false);
}

/* @overload tr_s(from, to)
 *
 *   Returns the receiver, translating characters in FROM to their equivalent
 *   character, by index, in TO and then squeezing any substrings of
 *   {#length} > 1 consisting of the same character _c_ with _c_, inheriting
 *   any taint and untrust.  If TO{#length} < FROM{#length}, TO[-1] will be
 *   used for any index _i_ > TO{#length}.
 *
 *   The complement of all Unicode characters and a given set of characters may
 *   be specified by prefixing a non-empty set with ‘`^`’ (U+005E CIRCUMFLEX
 *   ACCENT).
 *
 *   Any sequence of characters _a_-_b_ inside a set will expand to also
 *   include all characters whose code points lay between those of _a_ and _b_.
 *
 *   @param [#to_str] from
 *   @param [#to_str] to
 *   @return [U::String] */
VALUE
rb_u_string_tr_s(VALUE self, VALUE from, VALUE to)
{
        return tr_trans(self, from, to, true);
}
