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
	UNICODE_CONTROL,
	UNICODE_FORMAT,
	UNICODE_UNASSIGNED,
	UNICODE_PRIVATE_USE,
	UNICODE_SURROGATE,
	UNICODE_LOWERCASE_LETTER,
	UNICODE_MODIFIER_LETTER,
	UNICODE_OTHER_LETTER,
	UNICODE_TITLECASE_LETTER,
	UNICODE_UPPERCASE_LETTER,
	UNICODE_SPACING_MARK,
	UNICODE_ENCLOSING_MARK,
	UNICODE_NON_SPACING_MARK,
	UNICODE_DECIMAL_NUMBER,
	UNICODE_LETTER_NUMBER,
	UNICODE_OTHER_NUMBER,
	UNICODE_CONNECT_PUNCTUATION,
	UNICODE_DASH_PUNCTUATION,
	UNICODE_CLOSE_PUNCTUATION,
	UNICODE_FINAL_PUNCTUATION,
	UNICODE_INITIAL_PUNCTUATION,
	UNICODE_OTHER_PUNCTUATION,
	UNICODE_OPEN_PUNCTUATION,
	UNICODE_CURRENCY_SYMBOL,
	UNICODE_MODIFIER_SYMBOL,
	UNICODE_MATH_SYMBOL,
	UNICODE_OTHER_SYMBOL,
	UNICODE_LINE_SEPARATOR,
	UNICODE_PARAGRAPH_SEPARATOR,
	UNICODE_SPACE_SEPARATOR
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
	UNICODE_BREAK_MANDATORY,
	UNICODE_BREAK_CARRIAGE_RETURN,
	UNICODE_BREAK_LINE_FEED,
	UNICODE_BREAK_COMBINING_MARK,
	UNICODE_BREAK_SURROGATE,
	UNICODE_BREAK_ZERO_WIDTH_SPACE,
	UNICODE_BREAK_INSEPARABLE,
	UNICODE_BREAK_NON_BREAKING_GLUE,
	UNICODE_BREAK_CONTINGENT,
	UNICODE_BREAK_SPACE,
	UNICODE_BREAK_AFTER,
	UNICODE_BREAK_BEFORE,
	UNICODE_BREAK_BEFORE_AND_AFTER,
	UNICODE_BREAK_HYPHEN,
	UNICODE_BREAK_NON_STARTER,
	UNICODE_BREAK_OPEN_PUNCTUATION,
	UNICODE_BREAK_CLOSE_PUNCTUATION,
	UNICODE_BREAK_QUOTATION,
	UNICODE_BREAK_EXCLAMATION,
	UNICODE_BREAK_IDEOGRAPHIC,
	UNICODE_BREAK_NUMERIC,
	UNICODE_BREAK_INFIX_SEPARATOR,
	UNICODE_BREAK_SYMBOL,
	UNICODE_BREAK_ALPHABETIC,
	UNICODE_BREAK_PREFIX,
	UNICODE_BREAK_POSTFIX,
	UNICODE_BREAK_COMPLEX_CONTEXT,
	UNICODE_BREAK_AMBIGUOUS,
	UNICODE_BREAK_UNKNOWN,
	UNICODE_BREAK_NEXT_LINE,
	UNICODE_BREAK_WORD_JOINER,
        UNICODE_BREAK_HANGUL_L_JAMO,
        UNICODE_BREAK_HANGUL_V_JAMO,
        UNICODE_BREAK_HANGUL_T_JAMO,
        UNICODE_BREAK_HANGUL_LV_SYLLABLE,
        UNICODE_BREAK_HANGUL_LVT_SYLLABLE,
        UNICODE_BREAK_CLOSE_PARENTHESIS,
        UNICODE_BREAK_HEBREW_LETTER,
        UNICODE_BREAK_CONDITIONAL_JAPANESE_STARTER,
        UNICODE_BREAK_REGIONAL_INDICATOR
} UnicodeBreakType;

UnicodeBreakType unichar_break_type(unichar c);

typedef enum {
        UNICODE_WORD_BREAK_ALETTER,
        UNICODE_WORD_BREAK_CR,
        UNICODE_WORD_BREAK_EXTEND,
        UNICODE_WORD_BREAK_EXTENDNUMLET,
        UNICODE_WORD_BREAK_FORMAT,
        UNICODE_WORD_BREAK_KATAKANA,
        UNICODE_WORD_BREAK_LF,
        UNICODE_WORD_BREAK_MIDLETTER,
        UNICODE_WORD_BREAK_MIDNUM,
        UNICODE_WORD_BREAK_MIDNUMLET,
        UNICODE_WORD_BREAK_NEWLINE,
        UNICODE_WORD_BREAK_NUMERIC,
        UNICODE_WORD_BREAK_OTHER,
        UNICODE_WORD_BREAK_REGIONAL_INDICATOR,
} UnicodeWordBreakType;

UnicodeWordBreakType unichar_word_break_type(unichar c);


typedef enum {
        UNICODE_SCRIPT_COMMON,
        UNICODE_SCRIPT_INHERITED,
        UNICODE_SCRIPT_ARABIC,
        UNICODE_SCRIPT_ARMENIAN,
        UNICODE_SCRIPT_BENGALI,
        UNICODE_SCRIPT_BOPOMOFO,
        UNICODE_SCRIPT_CHEROKEE,
        UNICODE_SCRIPT_COPTIC,
        UNICODE_SCRIPT_CYRILLIC,
        UNICODE_SCRIPT_DESERET,
        UNICODE_SCRIPT_DEVANAGARI,
        UNICODE_SCRIPT_ETHIOPIC,
        UNICODE_SCRIPT_GEORGIAN,
        UNICODE_SCRIPT_GOTHIC,
        UNICODE_SCRIPT_GREEK,
        UNICODE_SCRIPT_GUJARATI,
        UNICODE_SCRIPT_GURMUKHI,
        UNICODE_SCRIPT_HAN,
        UNICODE_SCRIPT_HANGUL,
        UNICODE_SCRIPT_HEBREW,
        UNICODE_SCRIPT_HIRAGANA,
        UNICODE_SCRIPT_KANNADA,
        UNICODE_SCRIPT_KATAKANA,
        UNICODE_SCRIPT_KHMER,
        UNICODE_SCRIPT_LAO,
        UNICODE_SCRIPT_LATIN,
        UNICODE_SCRIPT_MALAYALAM,
        UNICODE_SCRIPT_MONGOLIAN,
        UNICODE_SCRIPT_MYANMAR,
        UNICODE_SCRIPT_OGHAM,
        UNICODE_SCRIPT_OLD_ITALIC,
        UNICODE_SCRIPT_ORIYA,
        UNICODE_SCRIPT_RUNIC,
        UNICODE_SCRIPT_SINHALA,
        UNICODE_SCRIPT_SYRIAC,
        UNICODE_SCRIPT_TAMIL,
        UNICODE_SCRIPT_TELUGU,
        UNICODE_SCRIPT_THAANA,
        UNICODE_SCRIPT_THAI,
        UNICODE_SCRIPT_TIBETAN,
        UNICODE_SCRIPT_CANADIAN_ABORIGINAL,
        UNICODE_SCRIPT_YI,
        UNICODE_SCRIPT_TAGALOG,
        UNICODE_SCRIPT_HANUNOO,
        UNICODE_SCRIPT_BUHID,
        UNICODE_SCRIPT_TAGBANWA,
        UNICODE_SCRIPT_BRAILLE,
        UNICODE_SCRIPT_CYPRIOT,
        UNICODE_SCRIPT_LIMBU,
        UNICODE_SCRIPT_OSMANYA,
        UNICODE_SCRIPT_SHAVIAN,
        UNICODE_SCRIPT_LINEAR_B,
        UNICODE_SCRIPT_TAI_LE,
        UNICODE_SCRIPT_UGARITIC,
        UNICODE_SCRIPT_NEW_TAI_LUE,
        UNICODE_SCRIPT_BUGINESE,
        UNICODE_SCRIPT_GLAGOLITIC,
        UNICODE_SCRIPT_TIFINAGH,
        UNICODE_SCRIPT_SYLOTI_NAGRI,
        UNICODE_SCRIPT_OLD_PERSIAN,
        UNICODE_SCRIPT_KHAROSHTHI,
        UNICODE_SCRIPT_UNKNOWN,
        UNICODE_SCRIPT_BALINESE,
        UNICODE_SCRIPT_CUNEIFORM,
        UNICODE_SCRIPT_PHOENICIAN,
        UNICODE_SCRIPT_PHAGS_PA,
        UNICODE_SCRIPT_NKO,
        UNICODE_SCRIPT_KAYAH_LI,
        UNICODE_SCRIPT_LEPCHA,
        UNICODE_SCRIPT_REJANG,
        UNICODE_SCRIPT_SUNDANESE,
        UNICODE_SCRIPT_SAURASHTRA,
        UNICODE_SCRIPT_CHAM,
        UNICODE_SCRIPT_OL_CHIKI,
        UNICODE_SCRIPT_VAI,
        UNICODE_SCRIPT_CARIAN,
        UNICODE_SCRIPT_LYCIAN,
        UNICODE_SCRIPT_LYDIAN,
        UNICODE_SCRIPT_AVESTAN,
        UNICODE_SCRIPT_BAMUM,
        UNICODE_SCRIPT_EGYPTIAN_HIEROGLYPHS,
        UNICODE_SCRIPT_IMPERIAL_ARAMAIC,
        UNICODE_SCRIPT_INSCRIPTIONAL_PAHLAVI,
        UNICODE_SCRIPT_INSCRIPTIONAL_PARTHIAN,
        UNICODE_SCRIPT_JAVANESE,
        UNICODE_SCRIPT_KAITHI,
        UNICODE_SCRIPT_LISU,
        UNICODE_SCRIPT_MEETEI_MAYEK,
        UNICODE_SCRIPT_OLD_SOUTH_ARABIAN,
        UNICODE_SCRIPT_OLD_TURKIC,
        UNICODE_SCRIPT_SAMARITAN,
        UNICODE_SCRIPT_TAI_THAM,
        UNICODE_SCRIPT_TAI_VIET,
        UNICODE_SCRIPT_BATAK,
        UNICODE_SCRIPT_BRAHMI,
        UNICODE_SCRIPT_MANDAIC,
        UNICODE_SCRIPT_MEROITIC_HIEROGLYPHS,
        UNICODE_SCRIPT_MEROITIC_CURSIVE,
        UNICODE_SCRIPT_SORA_SOMPENG,
        UNICODE_SCRIPT_CHAKMA,
        UNICODE_SCRIPT_SHARADA,
        UNICODE_SCRIPT_TAKRI,
        UNICODE_SCRIPT_MIAO,
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

typedef void (*UnicodeWordBreakFn)(const char *, void *);
void u_word_breaks(const char *string, size_t n, UnicodeWordBreakFn fn, void *closure);

int unichar_to_u(unichar c, char *result);
char *ucs4_to_u(unichar *str, size_t *items_read, size_t *items_written);
char *ucs4_to_u_n(unichar *str, size_t len, size_t *items_read, size_t *items_written);

#endif /* U_H */
