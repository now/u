struct tr {
        bool inside_range;
        uint32_t now;
        uint32_t max;
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

HIDDEN void tr_init(struct tr *tr, const char *p, const char *end);
HIDDEN bool tr_should_exclude(struct tr *tr);
HIDDEN enum tr_state tr_next(struct tr *t);
HIDDEN void tr_table_initialize(struct tr_table *table, VALUE rbstring);
HIDDEN void tr_table_initialize_from_strings(struct tr_table *table,
                                             int argc,
                                             VALUE *argv);
HIDDEN bool tr_table_lookup(struct tr_table *table, uint32_t c);
