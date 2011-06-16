#ifndef TYPES_H
#define TYPES_H


#define IS(type, class) (((unsigned int)1 << (type)) & (class))
#define OR(type, rest)  (((unsigned int)1 << (type)) | (rest))


HIDDEN extern const char (*_u_type_data)[256];
HIDDEN extern const int16_t *_u_type_table_part1;
HIDDEN extern const int16_t *_u_type_table_part2;


static inline int
s_type(unichar c)
{
	const int16_t *table;
	unsigned int page;

	if (c <= UNICODE_LAST_CHAR_PART1) {
		page = c >> 8;
		table = _u_type_table_part1;
	} else if (c >= UNICODE_FIRST_CHAR_PART2 && c <= UNICODE_LAST_CHAR) {
		page = (c - UNICODE_FIRST_CHAR_PART2) >> 8;
		table = _u_type_table_part2;
	} else {
		return UNICODE_UNASSIGNED;
	}

	if (table[page] >= UNICODE_MAX_TABLE_INDEX)
		return table[page] - UNICODE_MAX_TABLE_INDEX;
	else
		return _u_type_data[table[page]][c & 0xff];
}


static inline bool
s_isdigit(int type)
{
        return IS(type,
                  OR(UNICODE_DECIMAL_NUMBER,
                     OR(UNICODE_LETTER_NUMBER,
                        OR(UNICODE_OTHER_NUMBER, 0))));
}


static inline bool
s_isalpha(int type)
{
        return IS(type,
                  OR(UNICODE_LOWERCASE_LETTER,
                     OR(UNICODE_UPPERCASE_LETTER,
                        OR(UNICODE_TITLECASE_LETTER,
                           OR(UNICODE_MODIFIER_LETTER,
                              OR(UNICODE_OTHER_LETTER, 0))))));
}


static inline bool
s_ismark(int type)
{
        return IS(type,
                  OR(UNICODE_NON_SPACING_MARK,
                     OR(UNICODE_COMBINING_MARK,
                        OR(UNICODE_ENCLOSING_MARK, 0))));
}


#endif /* TYPES_H */
