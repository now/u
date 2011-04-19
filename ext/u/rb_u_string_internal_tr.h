/*
 * contents: Translation (#tr) related functions
 *
 * Copyright © 2006 Nikolai Weibull <now@bitwi.se>
 */

#ifndef RB_U_STRING_INTERNAL_TR_H
#define RB_U_STRING_INTERNAL_TR_H

struct tr {
        bool inside_range;
        unichar now;
        unichar max;
        const char *p;
        const char *end;
};

enum tr_state
{
        TR_FOUND,
        TR_READ_ANOTHER,
        TR_FINISHED
};

struct tr_table {
        bool exclude;
        bool continuous[256];
        VALUE sparse;
};

void tr_init(struct tr *tr, const char *p, const char *end) HIDDEN;
bool tr_should_exclude(struct tr *tr) HIDDEN;
enum tr_state tr_next(struct tr *t) HIDDEN;
void tr_table_initialize(struct tr_table *table, VALUE rbstring) HIDDEN;
void tr_table_initialize_from_strings(struct tr_table *table, int argc,
                                      VALUE *argv) HIDDEN;
bool tr_table_lookup(struct tr_table *table, unichar c) HIDDEN;

#endif /* RB_U_STRING_INTERNAL_TR_H */