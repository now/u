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
        int16_t index;

	if (c <= UNICODE_LAST_CHAR_PART1)
                index = _u_type_table_part1[c >> 8];
        else if (UNICODE_FIRST_CHAR_PART2 <= c && c <= UNICODE_LAST_CHAR)
                index = _u_type_table_part2[(c - UNICODE_FIRST_CHAR_PART2) >> 8];
	else
		return U_OTHER_NOT_ASSIGNED;

	if (index >= UNICODE_MAX_TABLE_INDEX)
		return index - UNICODE_MAX_TABLE_INDEX;

        return _u_type_data[index][c & 0xff];
}


static inline bool
s_isdigit(int type)
{
        return IS(type,
                  OR(U_NUMBER_DECIMAL,
                     OR(U_NUMBER_LETTER,
                        OR(U_NUMBER_OTHER, 0))));
}


static inline bool
s_isalpha(int type)
{
        return IS(type,
                  OR(U_LETTER_LOWERCASE,
                     OR(U_LETTER_UPPERCASE,
                        OR(U_LETTER_TITLECASE,
                           OR(U_LETTER_MODIFIER,
                              OR(U_LETTER_OTHER, 0))))));
}


static inline bool
s_ismark(int type)
{
        return IS(type,
                  OR(U_MARK_NON_SPACING,
                     OR(U_MARK_SPACING_COMBINING,
                        OR(U_MARK_ENCLOSING, 0))));
}


#endif /* TYPES_H */
