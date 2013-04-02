#if __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ > 4)
#  define U_CONST __attribute__((__const__))
#else
#  define U_CONST
#endif

#if __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ > 96)
#  define U_PURE __attribute__((__pure__))
#else
#  define U_PURE
#endif

#define U_CHAR_MAX UINT32_MAX

#define U_CHAR_MAX_BYTE_LENGTH 6

#define U_N_CODEPOINTS (0x10ffff + 1)

/* uint32_t return used for representing bad input to a function. */
#define U_BAD_INPUT_CHAR ((uint32_t)-1)


/* uint32_t return used for representing an incomplete input to a function. */
#define U_INCOMPLETE_INPUT_CHAR ((uint32_t)-2)


enum u_general_category {
        U_GENERAL_CATEGORY_OTHER_CONTROL,
        U_GENERAL_CATEGORY_OTHER_FORMAT,
        U_GENERAL_CATEGORY_OTHER_NOT_ASSIGNED,
        U_GENERAL_CATEGORY_OTHER_PRIVATE_USE,
        U_GENERAL_CATEGORY_OTHER_SURROGATE,
        U_GENERAL_CATEGORY_LETTER_LOWERCASE,
        U_GENERAL_CATEGORY_LETTER_MODIFIER,
        U_GENERAL_CATEGORY_LETTER_OTHER,
        U_GENERAL_CATEGORY_LETTER_TITLECASE,
        U_GENERAL_CATEGORY_LETTER_UPPERCASE,
        U_GENERAL_CATEGORY_MARK_SPACING_COMBINING,
        U_GENERAL_CATEGORY_MARK_ENCLOSING,
        U_GENERAL_CATEGORY_MARK_NON_SPACING,
        U_GENERAL_CATEGORY_NUMBER_DECIMAL,
        U_GENERAL_CATEGORY_NUMBER_LETTER,
        U_GENERAL_CATEGORY_NUMBER_OTHER,
        U_GENERAL_CATEGORY_PUNCTUATION_CONNECTOR,
        U_GENERAL_CATEGORY_PUNCTUATION_DASH,
        U_GENERAL_CATEGORY_PUNCTUATION_CLOSE,
        U_GENERAL_CATEGORY_PUNCTUATION_FINAL_QUOTE,
        U_GENERAL_CATEGORY_PUNCTUATION_INITIAL_QUOTE,
        U_GENERAL_CATEGORY_PUNCTUATION_OTHER,
        U_GENERAL_CATEGORY_PUNCTUATION_OPEN,
        U_GENERAL_CATEGORY_SYMBOL_CURRENCY,
        U_GENERAL_CATEGORY_SYMBOL_MODIFIER,
        U_GENERAL_CATEGORY_SYMBOL_MATH,
        U_GENERAL_CATEGORY_SYMBOL_OTHER,
        U_GENERAL_CATEGORY_SEPARATOR_LINE,
        U_GENERAL_CATEGORY_SEPARATOR_PARAGRAPH,
        U_GENERAL_CATEGORY_SEPARATOR_SPACE,
};

U_CONST bool u_char_isalnum(uint32_t c);
U_CONST bool u_char_isalpha(uint32_t c);
U_CONST bool u_char_isassigned(uint32_t c);
U_CONST bool u_char_iscased(uint32_t c);
U_CONST bool u_char_iscaseignorable(uint32_t c);
U_CONST bool u_char_iscntrl(uint32_t c);
U_CONST bool u_char_isdefined(uint32_t c);
U_CONST bool u_char_isdigit(uint32_t c);
U_CONST bool u_char_isgraph(uint32_t c);
U_CONST bool u_char_islower(uint32_t c);
U_CONST bool u_char_isnewline(uint32_t c);
U_CONST bool u_char_isprint(uint32_t c);
U_CONST bool u_char_ispunct(uint32_t c);
U_CONST bool u_char_issoftdotted(uint32_t c);
U_CONST bool u_char_isspace(uint32_t c);
U_CONST bool u_char_istitle(uint32_t c);
U_CONST bool u_char_isupper(uint32_t c);
U_CONST bool u_char_isvalid(uint32_t c);
U_CONST bool u_char_iswide(uint32_t c);
U_CONST bool u_char_iswide_cjk(uint32_t c);
U_CONST bool u_char_isxdigit(uint32_t c);
U_CONST bool u_char_iszerowidth(uint32_t c);

U_CONST uint32_t u_char_toupper(uint32_t c);
U_CONST uint32_t u_char_tolower(uint32_t c);
U_CONST uint32_t u_char_totitle(uint32_t c);

U_CONST size_t u_char_width(uint32_t c);

U_CONST int u_char_digit_value(uint32_t c);
U_CONST int u_char_xdigit_value(uint32_t c);

U_CONST enum u_general_category u_char_general_category(uint32_t c);

U_CONST int u_char_combining_class(uint32_t c);

bool u_char_mirror(uint32_t c, uint32_t *mirrored);


enum u_line_break {
        U_LINE_BREAK_MANDATORY,
        U_LINE_BREAK_CARRIAGE_RETURN,
        U_LINE_BREAK_LINE_FEED,
        U_LINE_BREAK_COMBINING_MARK,
        U_LINE_BREAK_NEXT_LINE,
        U_LINE_BREAK_SURROGATE,
        U_LINE_BREAK_WORD_JOINER,
        U_LINE_BREAK_ZERO_WIDTH_SPACE,
        U_LINE_BREAK_NON_BREAKING_GLUE,
        U_LINE_BREAK_SPACE,
        U_LINE_BREAK_BREAK_OPPORTUNITY_BEFORE_AND_AFTER,
        U_LINE_BREAK_BREAK_AFTER,
        U_LINE_BREAK_BREAK_BEFORE,
        U_LINE_BREAK_HYPHEN,
        U_LINE_BREAK_CONTINGENT_BREAK_OPPORTUNITY,
        U_LINE_BREAK_CLOSE_PUNCTUATION,
        U_LINE_BREAK_CLOSE_PARENTHESIS,
        U_LINE_BREAK_EXCLAMATION_INTERROGATION,
        U_LINE_BREAK_INSEPARABLE,
        U_LINE_BREAK_NONSTARTER,
        U_LINE_BREAK_OPEN_PUNCTUATION,
        U_LINE_BREAK_QUOTATION,
        U_LINE_BREAK_INFIX_NUMERIC_SEPARATOR,
        U_LINE_BREAK_NUMERIC,
        U_LINE_BREAK_POSTFIX_NUMERIC,
        U_LINE_BREAK_PREFIX_NUMERIC,
        U_LINE_BREAK_SYMBOLS_ALLOWING_BREAK_AFTER,
        U_LINE_BREAK_AMBIGUOUS,
        U_LINE_BREAK_ALPHABETIC,
        U_LINE_BREAK_CONDITIONAL_JAPANESE_STARTER,
        U_LINE_BREAK_HANGUL_LV_SYLLABLE,
        U_LINE_BREAK_HANGUL_LVT_SYLLABLE,
        U_LINE_BREAK_HEBREW_LETTER,
        U_LINE_BREAK_IDEOGRAPHIC,
        U_LINE_BREAK_HANGUL_L_JAMO,
        U_LINE_BREAK_HANGUL_V_JAMO,
        U_LINE_BREAK_HANGUL_T_JAMO,
        U_LINE_BREAK_REGIONAL_INDICATOR,
        U_LINE_BREAK_COMPLEX_CONTEXT_DEPENDENT,
        U_LINE_BREAK_UNKNOWN,
};

U_CONST enum u_line_break u_char_line_break(uint32_t c);

enum u_grapheme_break {
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
};

U_CONST enum u_grapheme_break u_char_grapheme_break(uint32_t c);

enum u_word_break {
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
};

U_CONST enum u_word_break u_char_word_break(uint32_t c);


enum u_script {
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
};

U_CONST enum u_script u_char_script(uint32_t c);

enum u_normalize_mode {
	U_NORMALIZE_DEFAULT,
	U_NORMALIZE_NFD = U_NORMALIZE_DEFAULT,
	U_NORMALIZE_DEFAULT_COMPOSE,
	U_NORMALIZE_NFC = U_NORMALIZE_DEFAULT_COMPOSE,
	U_NORMALIZE_ALL,
	U_NORMALIZE_NFKD = U_NORMALIZE_ALL,
	U_NORMALIZE_ALL_COMPOSE,
	U_NORMALIZE_NFKC = U_NORMALIZE_ALL_COMPOSE
};

char *u_normalize(const char *string, enum u_normalize_mode mode);
char *u_normalize_n(const char *string, size_t length,
                    enum u_normalize_mode mode, size_t *new_length);

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

U_PURE uint32_t u_aref_char(const char *str);
U_PURE uint32_t u_aref_char_n(const char *str, size_t max);
U_PURE uint32_t u_aref_char_validated(const char *str);
U_PURE uint32_t u_aref_char_validated_n(const char *str, size_t max);

extern const char * const u_skip_lengths;

#define u_next(str) ((str) + u_skip_lengths[*(const unsigned char *)(str)])
U_PURE char *u_find_next(const char *p, const char *end);

U_PURE char *u_prev(const char *p);
U_PURE char *u_find_prev(const char *begin, const char *p);

U_PURE char *u_offset_to_pointer(const char *str, long offset);
U_PURE char *u_offset_to_pointer_n(const char *str, long offset, size_t n);

U_PURE long u_pointer_to_offset(const char *str, const char *pos);

void u_copy(char *dest, const char *src);
void u_copy_n(char *dest, const char *src, size_t n);

void u_append(char *dest, const char *src);
void u_append_n(char *dest, const char *src, size_t n);

U_PURE int u_collate(const char *a, const char *b);
U_PURE int u_collate_n(const char *a, size_t a_len, const char *b, size_t b_len);
char *u_collate_key(const char *str);
char *u_collate_key_n(const char *str, size_t len, size_t *new_length);

U_PURE size_t u_char_index(const char *str, uint32_t c);
U_PURE size_t u_char_index_n(const char *str, uint32_t c, size_t len);
U_PURE size_t u_index(const char *haystack, const char *needle);
U_PURE size_t u_index_n(const char *haystack, const char *needle, size_t len);

U_PURE size_t u_char_rindex(const char *str, uint32_t c);
U_PURE size_t u_char_rindex_n(const char *str, uint32_t c, size_t len);
U_PURE size_t u_rindex(const char *haystack, const char *needle);
U_PURE size_t u_rindex_n(const char *haystack, const char *needle, size_t len);

U_PURE bool u_has_prefix(const char *str, const char *prefix);

U_PURE bool u_is_ascii_only(const char *string);
U_PURE bool u_is_ascii_only_n(const char *string, size_t length);

U_PURE long u_length(const char *str);
U_PURE long u_length_n(const char *str, long len);

U_PURE size_t u_width(const char *string);
U_PURE size_t u_width_n(const char *string, size_t length);

U_PURE size_t u_byte_length(const char *str);

char *u_reverse(const char *str);
char *u_reverse_n(const char *str, size_t len);

bool u_isvalid(const char *str);
bool u_isvalid_n(const char *str, size_t max, const char **end);

typedef void (*u_break_fn)(const char *, void *);
void u_word_breaks(const char *string, size_t n, u_break_fn fn, void *closure);
void u_grapheme_breaks(const char *string, size_t n, u_break_fn fn, void *closure);

int u_char_to_u(uint32_t c, char *result);
char *ucs4_to_u(uint32_t *str, size_t *items_read, size_t *items_written);
char *ucs4_to_u_n(uint32_t *str, size_t len, size_t *items_read, size_t *items_written);
