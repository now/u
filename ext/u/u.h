#ifndef U_H
#define U_H

#if __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ > 4)
#define CONST_FUNC                              \
          __attribute__((__const__))
#else
#define CONST_FUNC
#endif

typedef uint32_t unichar;

#define MAXUNICHAR UINT32_MAX

#define MAX_UNICHAR_BYTE_LENGTH 6

#define UNICODE_N_CODEPOINTS            (0x10ffff + 1)

/* unichar return used for representing bad input to a function. */
#define UTF_BAD_INPUT_UNICHAR		((unichar)-1)


/* unichar return used for representing an incomplete input to a function. */
#define UTF_INCOMPLETE_INPUT_UNICHAR	((unichar)-2)


typedef enum {
        U_OTHER_CONTROL,
        U_OTHER_FORMAT,
        U_OTHER_NOT_ASSIGNED,
        U_OTHER_PRIVATE_USE,
        U_OTHER_SURROGATE,
        U_LETTER_LOWERCASE,
        U_LETTER_MODIFIER,
        U_LETTER_OTHER,
        U_LETTER_TITLECASE,
        U_LETTER_UPPERCASE,
        U_MARK_SPACING_COMBINING,
        U_MARK_ENCLOSING,
        U_MARK_NON_SPACING,
        U_NUMBER_DECIMAL,
        U_NUMBER_LETTER,
        U_NUMBER_OTHER,
        U_PUNCTUATION_CONNECTOR,
        U_PUNCTUATION_DASH,
        U_PUNCTUATION_CLOSE,
        U_PUNCTUATION_FINAL_QUOTE,
        U_PUNCTUATION_INITIAL_QUOTE,
        U_PUNCTUATION_OTHER,
        U_PUNCTUATION_OPEN,
        U_SYMBOL_CURRENCY,
        U_SYMBOL_MODIFIER,
        U_SYMBOL_MATH,
        U_SYMBOL_OTHER,
        U_SEPARATOR_LINE,
        U_SEPARATOR_PARAGRAPH,
        U_SEPARATOR_SPACE,
} UnicodeType;

bool unichar_isalnum(unichar c);
bool unichar_isalpha(unichar c);
bool unichar_isassigned(unichar c);
bool unichar_iscased(unichar c);
bool unichar_iscaseignorable(unichar c);
bool unichar_iscntrl(unichar c);
bool unichar_isdefined(unichar c);
bool unichar_isdigit(unichar c);
bool unichar_isgraph(unichar c);
bool unichar_islower(unichar c);
bool unichar_isnewline(unichar c);
bool unichar_isprint(unichar c);
bool unichar_ispunct(unichar c);
bool unichar_issoftdotted(unichar c);
bool unichar_isspace(unichar c);
bool unichar_istitle(unichar c);
bool unichar_isupper(unichar c);
bool unichar_isvalid(unichar c);
bool unichar_iswide(unichar c);
bool unichar_iswide_cjk(unichar c);
bool unichar_isxdigit(unichar c);
bool unichar_iszerowidth(unichar c);

unichar unichar_toupper(unichar c);
unichar unichar_tolower(unichar c);
unichar unichar_totitle(unichar c);

size_t unichar_width(unichar c);

int unichar_digit_value(unichar c);
int unichar_xdigit_value(unichar c);

UnicodeType unichar_type(unichar c);

int unichar_combining_class(unichar c) CONST_FUNC;

bool unichar_mirror(unichar c, unichar *mirrored);


typedef enum {
	U_BREAK_MANDATORY,
	U_BREAK_CARRIAGE_RETURN,
	U_BREAK_LINE_FEED,
	U_BREAK_COMBINING_MARK,
	U_BREAK_SURROGATE,
	U_BREAK_ZERO_WIDTH_SPACE,
	U_BREAK_INSEPARABLE,
	U_BREAK_NON_BREAKING_GLUE,
	U_BREAK_CONTINGENT,
	U_BREAK_SPACE,
	U_BREAK_AFTER,
	U_BREAK_BEFORE,
	U_BREAK_BEFORE_AND_AFTER,
	U_BREAK_HYPHEN,
	U_BREAK_NON_STARTER,
	U_BREAK_OPEN_PUNCTUATION,
	U_BREAK_CLOSE_PUNCTUATION,
	U_BREAK_QUOTATION,
	U_BREAK_EXCLAMATION,
	U_BREAK_IDEOGRAPHIC,
	U_BREAK_NUMERIC,
	U_BREAK_INFIX_SEPARATOR,
	U_BREAK_SYMBOL,
	U_BREAK_ALPHABETIC,
	U_BREAK_PREFIX,
	U_BREAK_POSTFIX,
	U_BREAK_COMPLEX_CONTEXT,
	U_BREAK_AMBIGUOUS,
	U_BREAK_UNKNOWN,
	U_BREAK_NEXT_LINE,
	U_BREAK_WORD_JOINER,
        U_BREAK_HANGUL_L_JAMO,
        U_BREAK_HANGUL_V_JAMO,
        U_BREAK_HANGUL_T_JAMO,
        U_BREAK_HANGUL_LV_SYLLABLE,
        U_BREAK_HANGUL_LVT_SYLLABLE,
        U_BREAK_CLOSE_PARENTHESIS,
        U_BREAK_HEBREW_LETTER,
        U_BREAK_CONDITIONAL_JAPANESE_STARTER,
        U_BREAK_REGIONAL_INDICATOR
} UnicodeBreakType;

UnicodeBreakType unichar_break_type(unichar c);

typedef enum {
        U_GRAPHEME_BREAK_CONTROL,
        U_GRAPHEME_BREAK_CR,
        U_GRAPHEME_BREAK_EXTEND,
        U_GRAPHEME_BREAK_L,
        U_GRAPHEME_BREAK_LF,
        U_GRAPHEME_BREAK_LV,
        U_GRAPHEME_BREAK_LVT,
        U_GRAPHEME_BREAK_OTHER,
        U_GRAPHEME_BREAK_PREPEND,
        U_GRAPHEME_BREAK_REGIONAL_INDICATOR,
        U_GRAPHEME_BREAK_SPACINGMARK,
        U_GRAPHEME_BREAK_T,
        U_GRAPHEME_BREAK_V,
} UnicodeGraphemeBreakType;

UnicodeGraphemeBreakType unichar_grapheme_break_type(unichar c);

typedef enum {
        U_WORD_BREAK_ALETTER,
        U_WORD_BREAK_CR,
        U_WORD_BREAK_EXTEND,
        U_WORD_BREAK_EXTENDNUMLET,
        U_WORD_BREAK_FORMAT,
        U_WORD_BREAK_KATAKANA,
        U_WORD_BREAK_LF,
        U_WORD_BREAK_MIDLETTER,
        U_WORD_BREAK_MIDNUM,
        U_WORD_BREAK_MIDNUMLET,
        U_WORD_BREAK_NEWLINE,
        U_WORD_BREAK_NUMERIC,
        U_WORD_BREAK_OTHER,
        U_WORD_BREAK_REGIONAL_INDICATOR,
} UnicodeWordBreakType;

UnicodeWordBreakType unichar_word_break_type(unichar c);


typedef enum {
        U_SCRIPT_COMMON,
        U_SCRIPT_INHERITED,
        U_SCRIPT_ARABIC,
        U_SCRIPT_ARMENIAN,
        U_SCRIPT_BENGALI,
        U_SCRIPT_BOPOMOFO,
        U_SCRIPT_CHEROKEE,
        U_SCRIPT_COPTIC,
        U_SCRIPT_CYRILLIC,
        U_SCRIPT_DESERET,
        U_SCRIPT_DEVANAGARI,
        U_SCRIPT_ETHIOPIC,
        U_SCRIPT_GEORGIAN,
        U_SCRIPT_GOTHIC,
        U_SCRIPT_GREEK,
        U_SCRIPT_GUJARATI,
        U_SCRIPT_GURMUKHI,
        U_SCRIPT_HAN,
        U_SCRIPT_HANGUL,
        U_SCRIPT_HEBREW,
        U_SCRIPT_HIRAGANA,
        U_SCRIPT_KANNADA,
        U_SCRIPT_KATAKANA,
        U_SCRIPT_KHMER,
        U_SCRIPT_LAO,
        U_SCRIPT_LATIN,
        U_SCRIPT_MALAYALAM,
        U_SCRIPT_MONGOLIAN,
        U_SCRIPT_MYANMAR,
        U_SCRIPT_OGHAM,
        U_SCRIPT_OLD_ITALIC,
        U_SCRIPT_ORIYA,
        U_SCRIPT_RUNIC,
        U_SCRIPT_SINHALA,
        U_SCRIPT_SYRIAC,
        U_SCRIPT_TAMIL,
        U_SCRIPT_TELUGU,
        U_SCRIPT_THAANA,
        U_SCRIPT_THAI,
        U_SCRIPT_TIBETAN,
        U_SCRIPT_CANADIAN_ABORIGINAL,
        U_SCRIPT_YI,
        U_SCRIPT_TAGALOG,
        U_SCRIPT_HANUNOO,
        U_SCRIPT_BUHID,
        U_SCRIPT_TAGBANWA,
        U_SCRIPT_BRAILLE,
        U_SCRIPT_CYPRIOT,
        U_SCRIPT_LIMBU,
        U_SCRIPT_OSMANYA,
        U_SCRIPT_SHAVIAN,
        U_SCRIPT_LINEAR_B,
        U_SCRIPT_TAI_LE,
        U_SCRIPT_UGARITIC,
        U_SCRIPT_NEW_TAI_LUE,
        U_SCRIPT_BUGINESE,
        U_SCRIPT_GLAGOLITIC,
        U_SCRIPT_TIFINAGH,
        U_SCRIPT_SYLOTI_NAGRI,
        U_SCRIPT_OLD_PERSIAN,
        U_SCRIPT_KHAROSHTHI,
        U_SCRIPT_UNKNOWN,
        U_SCRIPT_BALINESE,
        U_SCRIPT_CUNEIFORM,
        U_SCRIPT_PHOENICIAN,
        U_SCRIPT_PHAGS_PA,
        U_SCRIPT_NKO,
        U_SCRIPT_KAYAH_LI,
        U_SCRIPT_LEPCHA,
        U_SCRIPT_REJANG,
        U_SCRIPT_SUNDANESE,
        U_SCRIPT_SAURASHTRA,
        U_SCRIPT_CHAM,
        U_SCRIPT_OL_CHIKI,
        U_SCRIPT_VAI,
        U_SCRIPT_CARIAN,
        U_SCRIPT_LYCIAN,
        U_SCRIPT_LYDIAN,
        U_SCRIPT_AVESTAN,
        U_SCRIPT_BAMUM,
        U_SCRIPT_EGYPTIAN_HIEROGLYPHS,
        U_SCRIPT_IMPERIAL_ARAMAIC,
        U_SCRIPT_INSCRIPTIONAL_PAHLAVI,
        U_SCRIPT_INSCRIPTIONAL_PARTHIAN,
        U_SCRIPT_JAVANESE,
        U_SCRIPT_KAITHI,
        U_SCRIPT_LISU,
        U_SCRIPT_MEETEI_MAYEK,
        U_SCRIPT_OLD_SOUTH_ARABIAN,
        U_SCRIPT_OLD_TURKIC,
        U_SCRIPT_SAMARITAN,
        U_SCRIPT_TAI_THAM,
        U_SCRIPT_TAI_VIET,
        U_SCRIPT_BATAK,
        U_SCRIPT_BRAHMI,
        U_SCRIPT_MANDAIC,
        U_SCRIPT_MEROITIC_HIEROGLYPHS,
        U_SCRIPT_MEROITIC_CURSIVE,
        U_SCRIPT_SORA_SOMPENG,
        U_SCRIPT_CHAKMA,
        U_SCRIPT_SHARADA,
        U_SCRIPT_TAKRI,
        U_SCRIPT_MIAO,
} UnicodeScript;

UnicodeScript unichar_script(unichar c);

typedef enum {
	NORMALIZE_DEFAULT,
	NORMALIZE_NFD = NORMALIZE_DEFAULT,
	NORMALIZE_DEFAULT_COMPOSE,
	NORMALIZE_NFC = NORMALIZE_DEFAULT_COMPOSE,
	NORMALIZE_ALL,
	NORMALIZE_NFKD = NORMALIZE_ALL,
	NORMALIZE_ALL_COMPOSE,
	NORMALIZE_NFKC = NORMALIZE_ALL_COMPOSE
} NormalizeMode;

char *u_normalize(const char *string, NormalizeMode mode);
char *u_normalize_n(const char *string, size_t length, NormalizeMode mode, size_t *new_length);

char *u_downcase(const char *string);
char *u_downcase_n(const char *string, size_t length, size_t *new_length);
char *u_downcase_in_locale(const char *string, const char *locale);
char *u_downcase_in_locale_n(const char *string, size_t length,
                             const char *locale, size_t *new_length);

char *u_foldcase(const char *string);
char *u_foldcase_n(const char *string, size_t length, size_t *new_length);

char *u_titlecase(const char *string);
char *u_titlecase_n(const char *string, size_t length, size_t *new_length);
char *u_titlecase_in_locale(const char *string, const char *locale);
char *u_titlecase_in_locale_n(const char *string, size_t length,
                              const char *locale, size_t *new_length);

char *u_upcase(const char *string);
char *u_upcase_n(const char *string, size_t length, size_t *new_length);
char *u_upcase_in_locale(const char *string, const char *locale);
char *u_upcase_in_locale_n(const char *string, size_t length,
                           const char *locale, size_t *new_length);

unichar u_aref_char(const char *str);
unichar u_aref_char_n(const char *str, size_t max);
unichar u_aref_char_validated(const char *str);
unichar u_aref_char_validated_n(const char *str, size_t max);

extern const char * const u_skip_lengths;

#define u_next(str) ((str) + u_skip_lengths[*(const unsigned char *)(str)])
char *u_find_next(const char *p, const char *end);

char *u_prev(const char *p);
char *u_find_prev(const char *begin, const char *p);

char *u_offset_to_pointer(const char *str, long offset);
char *u_offset_to_pointer_n(const char *str, long offset, size_t n);

long u_pointer_to_offset(const char *str, const char *pos);

void u_copy(char *dest, const char *src);
void u_copy_n(char *dest, const char *src, size_t n);

void u_append(char *dest, const char *src);
void u_append_n(char *dest, const char *src, size_t n);

int u_collate(const char *a, const char *b);
int u_collate_n(const char *a, size_t a_len, const char *b, size_t b_len);
char *u_collate_key(const char *str);
char *u_collate_key_n(const char *str, size_t len, size_t *new_length);

size_t u_char_index(const char *str, unichar c);
size_t u_char_index_n(const char *str, unichar c, size_t len);
size_t u_index(const char *haystack, const char *needle);
size_t u_index_n(const char *haystack, const char *needle, size_t len);

size_t u_char_rindex(const char *str, unichar c);
size_t u_char_rindex_n(const char *str, unichar c, size_t len);
size_t u_rindex(const char *haystack, const char *needle);
size_t u_rindex_n(const char *haystack, const char *needle, size_t len);

bool utf_has_prefix(const char *str, const char *prefix);

bool u_is_ascii_only(const char *string);
bool u_is_ascii_only_n(const char *string, size_t length);

long u_length(const char *str);
long u_length_n(const char *str, long len);

size_t u_width(const char *string);
size_t u_width_n(const char *string, size_t length);

size_t u_byte_length(const char *str);

char *u_reverse(const char *str);
char *u_reverse_n(const char *str, size_t len);

bool u_isvalid(const char *str);
bool u_isvalid_n(const char *str, size_t max, const char **end);

typedef void (*UnicodeBreakFn)(const char *, void *);
void u_word_breaks(const char *string, size_t n, UnicodeBreakFn fn, void *closure);
void u_grapheme_breaks(const char *string, size_t n, UnicodeBreakFn fn, void *closure);

int unichar_to_u(unichar c, char *result);
char *ucs4_to_u(unichar *str, size_t *items_read, size_t *items_written);
char *ucs4_to_u_n(unichar *str, size_t len, size_t *items_read, size_t *items_written);

#endif /* U_H */
