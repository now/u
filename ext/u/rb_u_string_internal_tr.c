#include "rb_includes.h"
#include "rb_u_string_internal_tr.h"

void
tr_init(struct tr *tr, const char *p, const char *end)
{
        tr->p = p;
        tr->end = end;
        tr->inside_range = false;
}

bool
tr_should_exclude(struct tr *tr)
{
        if (tr->p + 1 < tr->end && *tr->p == '^') {
                tr->p++;
                return true;
        }

        return false;
}

static enum tr_state
tr_next_char(struct tr *t)
{
        if (t->p == t->end)
                return TR_FINISHED;

        if (_rb_u_dref(t->p, t->end) == '\\') {
                const char *next = u_find_next(t->p, t->end);

                if (next == NULL) {
                        t->now = '\\';
                        t->p = t->end;
                        return TR_FOUND;
                }

                t->p = next;
        }

        t->now = _rb_u_dref(t->p, t->end);

        const char *next = u_find_next(t->p, t->end);
        if (next == NULL) {
                t->p = t->end;
                return TR_FOUND;
        }
        t->p = next;

        if (_rb_u_dref(t->p, t->end) == '-') {
                next = u_find_next(t->p, t->end);
                /* TODO: Make this simpler.  Perhaps we don’t need
                 * TR_READ_ANOTHER, as we advance it here ourselves.  I got to
                 * check the offsets here.  Perhaps TR_READ_ANOTHER should also
                 * have advanced t->p one more step. */
                if (next != NULL) {
                        uint32_t max = u_dref(next);

                        if (max < t->now) {
                                t->p = next;
                                return TR_READ_ANOTHER;
                        }

                        t->inside_range = true;
                        t->max = max;

                        next = u_find_next(next, t->end);
                        t->p = (next != NULL) ? next : t->end;
                }
        }

        return TR_FOUND;
}

enum tr_state
tr_next(struct tr *t)
{
        while (true) {
                if (!t->inside_range) {
                        enum tr_state state;

                        if ((state = tr_next_char(t)) == TR_READ_ANOTHER)
                                continue;

                        return state;
                } else if (++t->now < t->max) {
                        return TR_FOUND;
                } else {
                        t->inside_range = false;
                        return TR_FOUND;
                }
        }
}

static void
tr_table_set(struct tr_table *table, bool *buffer, uint32_t c, bool value)
{
        if (c < lengthof(table->continuous)) {
                buffer[c] = value;
                return;
        }

        if (NIL_P(table->sparse))
                table->sparse = rb_hash_new();

        rb_hash_aset(table->sparse, UINT2NUM(c), value ? Qtrue : Qfalse);
}

static void
tr_table_add(struct tr_table *table, const struct rb_u_string *string)
{
        struct tr tr;
        tr_init(&tr, USTRING_STR(string), USTRING_END(string));

        bool exclude = tr_should_exclude(&tr);

        bool buffer[lengthof(table->continuous)];

        for (size_t i = 0; i < lengthof(buffer); i++)
                buffer[i] = exclude;

        while (tr_next(&tr) != TR_FINISHED)
                tr_table_set(table, buffer, tr.now, !exclude);

        for (size_t i = 0; i < lengthof(table->continuous); i++)
                table->continuous[i] = table->continuous[i] && buffer[i];
}

void
tr_table_initialize(struct tr_table *table, VALUE rbstring)
{
        const struct rb_u_string *string = RVAL2USTRING_ANY(rbstring);

        struct tr tr;
        tr_init(&tr, USTRING_STR(string), USTRING_END(string));

        table->exclude = tr_should_exclude(&tr);

        for (size_t i = 0; i < lengthof(table->continuous); i++)
                table->continuous[i] = true;

        table->sparse = Qnil;

        tr_table_add(table, string);
}

void
tr_table_initialize_from_strings(struct tr_table *table, int argc, VALUE *argv)
{
    tr_table_initialize(table, argv[0]);
    for (int i = 1; i < argc; i++)
            tr_table_add(table, RVAL2USTRING_ANY(argv[i]));
}

bool
tr_table_lookup(struct tr_table *table, uint32_t c)
{
        if (c < lengthof(table->continuous))
                return table->continuous[c];

        VALUE value = NIL_P(table->sparse) ?
                Qnil : rb_hash_lookup(table->sparse, UINT2NUM(c));

        return NIL_P(value) ? table->exclude : RTEST(value);
}
