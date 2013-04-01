#ifndef COMBINING_CLASS_H
#define COMBINING_CLASS_H


HIDDEN extern const uint8_t (*_u_combining_class_data)[256];
HIDDEN extern const int16_t *_u_combining_class_table_part1;
HIDDEN extern const int16_t *_u_combining_class_table_part2;


static inline int
s_combining_class(uint32_t c)
{
        int16_t index;

	if (c <= UNICODE_LAST_CHAR_PART1)
                index = _u_combining_class_table_part1[c >> 8];
        else if (UNICODE_FIRST_CHAR_PART2 <= c && c <= UNICODE_LAST_CHAR)
                index = _u_combining_class_table_part2[(c - UNICODE_FIRST_CHAR_PART2) >> 8];
	else
		return 0;

	if (index >= UNICODE_MAX_TABLE_INDEX)
		return index - UNICODE_MAX_TABLE_INDEX;

        return _u_combining_class_data[index][c & 0xff];
}


#endif /* COMBINING_CLASS_H */
