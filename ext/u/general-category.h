#define IS(type, class) (((unsigned int)1 << (type)) & (class))
#define OR(type, rest)  (((unsigned int)1 << (type)) | (rest))


extern const uint8_t (*_u_general_category_data)[256];
extern const int16_t *_u_general_category_table_part1;
extern const int16_t *_u_general_category_table_part2;


static inline int
s_general_category(uint32_t c)
{
        int16_t index;

	if (c <= UNICODE_LAST_CHAR_PART1)
                index = _u_general_category_table_part1[c >> 8];
        else if (UNICODE_FIRST_CHAR_PART2 <= c && c <= UNICODE_LAST_CHAR)
                index = _u_general_category_table_part2[(c - UNICODE_FIRST_CHAR_PART2) >> 8];
	else
		return U_GENERAL_CATEGORY_OTHER_NOT_ASSIGNED;

	if (index >= UNICODE_MAX_TABLE_INDEX)
		return index - UNICODE_MAX_TABLE_INDEX;

        return _u_general_category_data[index][c & 0xff];
}


static inline bool
s_isdigit(int category)
{
        return IS(category,
                  OR(U_GENERAL_CATEGORY_NUMBER_DECIMAL,
                     OR(U_GENERAL_CATEGORY_NUMBER_LETTER,
                        OR(U_GENERAL_CATEGORY_NUMBER_OTHER, 0))));
}


static inline bool
s_isalpha(int category)
{
        return IS(category,
                  OR(U_GENERAL_CATEGORY_LETTER_LOWERCASE,
                     OR(U_GENERAL_CATEGORY_LETTER_UPPERCASE,
                        OR(U_GENERAL_CATEGORY_LETTER_TITLECASE,
                           OR(U_GENERAL_CATEGORY_LETTER_MODIFIER,
                              OR(U_GENERAL_CATEGORY_LETTER_OTHER, 0))))));
}
