struct output {
        size_t n;
        char *result;
};

#define OUTPUT_INIT { 0, NULL }

static struct output *
output_char(struct output *output, uint32_t c)
{
        output->n += u_char_to_u(c, OFFSET_IF(output->result, output->n));
        return output;
}

static struct output *
output_string(struct output *output, const char *string, size_t n)
{
        if (output->result)
                memcpy(output->result + output->n, string, n);
        output->n += n;
        return output;
}

static struct output *
output_zstring(struct output *output, const char *string)
{
        return output_string(output, string, u_n_bytes(string));
}

static struct output *
output_alloc(struct output *output)
{
        output->result = malloc(output->n + 1);
        output->n = 0;
        return output;
}

static char *
output_finalize(struct output *output, size_t *n)
{
        output->result[output->n] = '\0';
        if (n != NULL)
                *n = output->n;
        char *r = output->result;
        *output = (struct output)OUTPUT_INIT;
        return r;
}
