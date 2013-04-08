#ifndef UNIT
#  define UNIT char
#  define UNIT_TO_U u_char_to_u
#  define UNIT_N_BYTES u_n_bytes
#endif

struct output {
        size_t n;
        UNIT *result;
};

#define OUTPUT_INIT { 0, NULL }

static inline struct output *
output_char(struct output *output, uint32_t c)
{
        output->n += UNIT_TO_U(c, OFFSET_IF(output->result, output->n));
        return output;
}

#ifdef UNIT_N_BYTES
static inline struct output *
output_string(struct output *output, const UNIT *string, size_t n)
{
        if (output->result)
                memcpy(output->result + output->n, string, sizeof(UNIT) * n);
        output->n += n;
        return output;
}

static inline struct output *
output_zstring(struct output *output, const UNIT *string)
{
        return output_string(output, string, UNIT_N_BYTES(string));
}
#endif

static inline struct output *
output_alloc(struct output *output)
{
        output->result = malloc(sizeof(UNIT) * (output->n + 1));
        output->n = 0;
        return output;
}

static inline UNIT *
output_finalize(struct output *output, size_t *n)
{
        output->result[output->n] = '\0';
        if (n != NULL)
                *n = output->n;
        UNIT *r = output->result;
        *output = (struct output)OUTPUT_INIT;
        return r;
}
