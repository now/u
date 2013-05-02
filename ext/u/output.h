#ifndef UNIT
#  define UNIT char
#  define UNIT_TO_U u_char_to_u_n
#  define UNIT_N_BYTES u_n_bytes
#endif

struct output {
        UNIT *result;
        size_t m;
        size_t n;
};

#define OUTPUT_INIT(result, m) { result, m, 0 }

static inline struct output *
output_char(struct output *output, uint32_t c)
{
        output->n += UNIT_TO_U(c, OFFSET_IF(output->result, output->n),
                               output->m > output->n ?
                               output->m - output->n - 1 :
                               0);
        return output;
}

#ifdef UNIT_N_BYTES
static inline struct output *
output_string(struct output *output, const UNIT *string, size_t n)
{
        if (output->m > output->n + n)
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

static inline size_t
output_finalize(struct output *output)
{
        if (output->m > output->n)
                output->result[output->n] = '\0';
        return output->n;
}
