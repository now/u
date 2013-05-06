void _u_downcase_step(const char *string, const char *p, const char *end,
                      enum locale locale, struct output *output);

void _u_upcase_step(const char *string, const char **p, const char *end,
                    enum locale locale, bool title, struct output *output);

static inline void
case_simple(uint32_t c, enum u_general_category category, bool title, bool upper, struct output *output)
{
	uint32_t v = _u_attribute(c);
        uint32_t u;
	if (v >= UNICODE_SPECIAL_CASE_TABLE_START)
                output_zstring(output, _u_special_case(v, category, title));
        else if (category == U_GENERAL_CATEGORY_LETTER_TITLECASE &&
                 (u = _u_titlecase_table_lookup(c, upper)) != c)
                output_char(output, u);
        else
                output_char(output, v != '\0' ? v : c);
}

static inline bool
is_after(const char *string, const char *p, bool predicate(uint32_t))
{
        if (p == string)
                return false;
        for (const char *q = u_prev(p); q > string; q = u_prev(q)) {
                uint32_t c = u_dref(q);
                if (predicate(c))
                        return true;
                switch (u_char_canonical_combining_class(u_dref(p))) {
                case U_CANONICAL_COMBINING_CLASS_ABOVE:
                case U_CANONICAL_COMBINING_CLASS_NOT_REORDERED:
                        return false;
                default:
                        break;
                }
	}
        return predicate(u_dref(string));
}
