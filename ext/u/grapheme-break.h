HIDDEN extern const uint8_t (*_u_grapheme_break_property_data)[256];
HIDDEN extern const int16_t *_u_grapheme_break_property_table_part1;
HIDDEN extern const int16_t *_u_grapheme_break_property_table_part2;


static inline UnicodeGraphemeBreak
s_grapheme_break(uint32_t c)
{
        int16_t index;

	if (c <= UNICODE_LAST_CHAR_PART1)
                index = _u_grapheme_break_property_table_part1[c >> 8];
        else if (UNICODE_FIRST_CHAR_PART2 <= c && c <= UNICODE_LAST_CHAR)
                index = _u_grapheme_break_property_table_part2[(c - UNICODE_FIRST_CHAR_PART2) >> 8];
	else
		return U_GRAPHEME_BREAK_OTHER;

	if (index >= UNICODE_MAX_TABLE_INDEX)
		return index - UNICODE_MAX_TABLE_INDEX;

        return _u_grapheme_break_property_data[index][c & 0xff];
}
