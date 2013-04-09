struct yield {
        void (*call)(struct yield *, VALUE value);
};

#define YIELD_INIT { yield };

static void
yield(UNUSED(struct yield *yield), VALUE value)
{
        rb_yield(value);
}

struct yield_array {
        struct yield yield;
        VALUE array;
};

#define YIELD_ARRAY_INIT { { yield_array }, rb_ary_new() }

static void
yield_array(struct yield *yield, VALUE value)
{
        rb_ary_push(((struct yield_array *)yield)->array, value);
}

#define yield_call(yield, value)                                   \
        (((struct yield *)(yield))->call((struct yield *)(yield), (value)))
