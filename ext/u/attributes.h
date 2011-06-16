#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H


HIDDEN extern const unichar (*_u_attr_data)[256];
HIDDEN extern const int16_t *_u_attr_table_part1;
HIDDEN extern const int16_t *_u_attr_table_part2;
HIDDEN extern const char *_u_special_case_table;


static inline unichar
s_attribute(unichar c)
{
        unichar page = c >> 8;
        /* 0xe00 == UNICODE_FIRST_CHAR_PART2 / 256 */
        unichar index = page <= UNICODE_LAST_PAGE_PART1 ?
                _u_attr_table_part1[page] :
                _u_attr_table_part2[page - 0xe00];

        if (index == UNICODE_MAX_TABLE_INDEX)
                return 0;

        return _u_attr_data[index][c & 0xff];
}

unichar _u_special_case_table_lookup(unichar c);
size_t _u_special_case_output(char *buf, int offset, int type, bool upper);


#endif /* ATTRIBUTES_H */
