extern const uint32_t (*_u_attr_data)[256];
extern const int16_t *_u_attr_table_part1;
extern const int16_t *_u_attr_table_part2;
extern const char *_u_special_case_table;


/* This function may only be called if C has been verified to be of a
 * UnicodeType that supports attributes, as it doesn’t perform bounds checking
 * on C. */
static inline uint32_t
s_attribute(uint32_t c)
{
        uint32_t page = c >> 8;
        uint32_t index = page <= UNICODE_LAST_PAGE_PART1 ?
                _u_attr_table_part1[page] :
                _u_attr_table_part2[(c - UNICODE_FIRST_CHAR_PART2) >> 8];

        if (index == UNICODE_MAX_TABLE_INDEX)
                return 0;

        return _u_attr_data[index][c & 0xff];
}

uint32_t _u_special_case_table_lookup(uint32_t c);
size_t _u_special_case_output(char *buf, int offset, int type, bool upper);
