/* Automatically generated file */

struct unichar_interval {
  unichar first;
  unichar last;
};

static int
unichar_interval_compare(const void *key, const void *element)
{
        unichar c = *(unichar *)key;
        struct unichar_interval *interval = (struct unichar_interval *)element;

        if (c < interval->first)
                return -1;
        else if (c > interval->last)
                return +1;
        else
                return 0;
}


static const struct unichar_interval cased[] = {
	{ 0x00aa, 0x00aa },
	{ 0x00ba, 0x00ba },
	{ 0x02b0, 0x02b8 },
	{ 0x02c0, 0x02c1 },
	{ 0x02e0, 0x02e4 },
	{ 0x0345, 0x0345 },
	{ 0x037a, 0x037a },
	{ 0x1d2c, 0x1d6a },
	{ 0x1d78, 0x1d78 },
	{ 0x1d9b, 0x1dbf },
	{ 0x2071, 0x2071 },
	{ 0x207f, 0x207f },
	{ 0x2090, 0x209c },
	{ 0x2160, 0x217f },
	{ 0x24b6, 0x24e9 },
	{ 0x2c7c, 0x2c7d },
	{ 0xa770, 0xa770 },
	{ 0xa7f8, 0xa7f9 }
};
