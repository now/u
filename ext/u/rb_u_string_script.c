#include "rb_includes.h"

#define SCRIPT2ID(script, symbol) \
        case U_SCRIPT_##script: { \
                static ID id_##symbol; \
                if (id_##symbol == 0) \
                        id_##symbol = rb_intern(#symbol); \
                return ID2SYM(id_##symbol); \
        }

static VALUE
script_to_symbol(UnicodeScript script)
{
        switch (script) {
        SCRIPT2ID(COMMON, common)
        SCRIPT2ID(INHERITED, inherited)
        SCRIPT2ID(ARABIC, arabic)
        SCRIPT2ID(ARMENIAN, armenian)
        SCRIPT2ID(BENGALI, bengali)
        SCRIPT2ID(BOPOMOFO, bopomofo)
        SCRIPT2ID(CHEROKEE, cherokee)
        SCRIPT2ID(COPTIC, coptic)
        SCRIPT2ID(CYRILLIC, cyrillic)
        SCRIPT2ID(DESERET, deseret)
        SCRIPT2ID(DEVANAGARI, devanagari)
        SCRIPT2ID(ETHIOPIC, ethiopic)
        SCRIPT2ID(GEORGIAN, georgian)
        SCRIPT2ID(GOTHIC, gothic)
        SCRIPT2ID(GREEK, greek)
        SCRIPT2ID(GUJARATI, gujarati)
        SCRIPT2ID(GURMUKHI, gurmukhi)
        SCRIPT2ID(HAN, han)
        SCRIPT2ID(HANGUL, hangul)
        SCRIPT2ID(HEBREW, hebrew)
        SCRIPT2ID(HIRAGANA, hiragana)
        SCRIPT2ID(KANNADA, kannada)
        SCRIPT2ID(KATAKANA, katakana)
        SCRIPT2ID(KHMER, khmer)
        SCRIPT2ID(LAO, lao)
        SCRIPT2ID(LATIN, latin)
        SCRIPT2ID(MALAYALAM, malayalam)
        SCRIPT2ID(MONGOLIAN, mongolian)
        SCRIPT2ID(MYANMAR, myanmar)
        SCRIPT2ID(OGHAM, ogham)
        SCRIPT2ID(OLD_ITALIC, old_italic)
        SCRIPT2ID(ORIYA, oriya)
        SCRIPT2ID(RUNIC, runic)
        SCRIPT2ID(SINHALA, sinhala)
        SCRIPT2ID(SYRIAC, syriac)
        SCRIPT2ID(TAMIL, tamil)
        SCRIPT2ID(TELUGU, telugu)
        SCRIPT2ID(THAANA, thaana)
        SCRIPT2ID(THAI, thai)
        SCRIPT2ID(TIBETAN, tibetan)
        SCRIPT2ID(CANADIAN_ABORIGINAL, canadian_aboriginal)
        SCRIPT2ID(YI, yi)
        SCRIPT2ID(TAGALOG, tagalog)
        SCRIPT2ID(HANUNOO, hanunoo)
        SCRIPT2ID(BUHID, buhid)
        SCRIPT2ID(TAGBANWA, tagbanwa)
        SCRIPT2ID(BRAILLE, braille)
        SCRIPT2ID(CYPRIOT, cypriot)
        SCRIPT2ID(LIMBU, limbu)
        SCRIPT2ID(OSMANYA, osmanya)
        SCRIPT2ID(SHAVIAN, shavian)
        SCRIPT2ID(LINEAR_B, linear_b)
        SCRIPT2ID(TAI_LE, tai_le)
        SCRIPT2ID(UGARITIC, ugaritic)
        SCRIPT2ID(NEW_TAI_LUE, new_tai_lue)
        SCRIPT2ID(BUGINESE, buginese)
        SCRIPT2ID(GLAGOLITIC, glagolitic)
        SCRIPT2ID(TIFINAGH, tifinagh)
        SCRIPT2ID(SYLOTI_NAGRI, syloti_nagri)
        SCRIPT2ID(OLD_PERSIAN, old_persian)
        SCRIPT2ID(KHAROSHTHI, kharoshthi)
        SCRIPT2ID(UNKNOWN, unknown)
        SCRIPT2ID(BALINESE, balinese)
        SCRIPT2ID(CUNEIFORM, cuneiform)
        SCRIPT2ID(PHOENICIAN, phoenician)
        SCRIPT2ID(PHAGS_PA, phags_pa)
        SCRIPT2ID(NKO, nko)
        SCRIPT2ID(KAYAH_LI, kayah_li)
        SCRIPT2ID(LEPCHA, lepcha)
        SCRIPT2ID(REJANG, rejang)
        SCRIPT2ID(SUNDANESE, sundanese)
        SCRIPT2ID(SAURASHTRA, saurashtra)
        SCRIPT2ID(CHAM, cham)
        SCRIPT2ID(OL_CHIKI, ol_chiki)
        SCRIPT2ID(VAI, vai)
        SCRIPT2ID(CARIAN, carian)
        SCRIPT2ID(LYCIAN, lycian)
        SCRIPT2ID(LYDIAN, lydian)
        SCRIPT2ID(AVESTAN, avestan)
        SCRIPT2ID(BAMUM, bamum)
        SCRIPT2ID(EGYPTIAN_HIEROGLYPHS, egyptian_hieroglyphs)
        SCRIPT2ID(IMPERIAL_ARAMAIC, imperial_aramaic)
        SCRIPT2ID(INSCRIPTIONAL_PAHLAVI, inscriptional_pahlavi)
        SCRIPT2ID(INSCRIPTIONAL_PARTHIAN, inscriptional_parthian)
        SCRIPT2ID(JAVANESE, javanese)
        SCRIPT2ID(KAITHI, kaithi)
        SCRIPT2ID(LISU, lisu)
        SCRIPT2ID(MEETEI_MAYEK, meetei_mayek)
        SCRIPT2ID(OLD_SOUTH_ARABIAN, old_south_arabian)
        SCRIPT2ID(OLD_TURKIC, old_turkic)
        SCRIPT2ID(SAMARITAN, samaritan)
        SCRIPT2ID(TAI_THAM, tai_tham)
        SCRIPT2ID(TAI_VIET, tai_viet)
        SCRIPT2ID(BATAK, batak)
        SCRIPT2ID(BRAHMI, brahmi)
        SCRIPT2ID(MANDAIC, mandaic)
        SCRIPT2ID(MEROITIC_HIEROGLYPHS, meroitic_hieroglyphs)
        SCRIPT2ID(MEROITIC_CURSIVE, meroitic_cursive)
        SCRIPT2ID(SORA_SOMPENG, sora_sompeng)
        SCRIPT2ID(CHAKMA, chakma)
        SCRIPT2ID(SHARADA, sharada)
        SCRIPT2ID(TAKRI, takri)
        SCRIPT2ID(MIAO, miao)
        default:
                rb_u_raise(rb_eNotImpError, "unknown script: %d", script);
        }
}

/* Returns the script of the characters of the receiver.
 *
 * The script of a character identifies the primary writing system that uses
 * the character.
 *
 * <table>
 *   <thead><tr><th>Script</th><th>Description</th></tr></thead>
 *   <tbody>
 *     <tr><td>:arabic</td><td>Arabic</td></tr>
 *     <tr><td>:armenian</td><td>Armenian</td></tr>
 *     <tr><td>:avestan</td><td>Avestan</td></tr>
 *     <tr><td>:balinese</td><td>Balinese</td></tr>
 *     <tr><td>:bamum</td><td>Bamum</td></tr>
 *     <tr><td>:batak</td><td>Batak</td></tr>
 *     <tr><td>:bengali</td><td>Bengali</td></tr>
 *     <tr><td>:bopomofo</td><td>Bopomofo</td></tr>
 *     <tr><td>:brahmi</td><td>Brahmi</td></tr>
 *     <tr><td>:braille</td><td>Braille</td></tr>
 *     <tr><td>:buginese</td><td>Buginese</td></tr>
 *     <tr><td>:buhid</td><td>Buhid</td></tr>
 *     <tr><td>:canadian_aboriginal</td><td>Canadian Aboriginal</td></tr>
 *     <tr><td>:carian</td><td>Carian</td></tr>
 *     <tr><td>:chakma</td><td>Chakma</td></tr>
 *     <tr><td>:cham</td><td>Cham</td></tr>
 *     <tr><td>:cherokee</td><td>Cherokee</td></tr>
 *     <tr><td>:common</td><td>For other characters that may be used with multiple scripts</td></tr>
 *     <tr><td>:coptic</td><td>Coptic</td></tr>
 *     <tr><td>:cuneiform</td><td>Cuneiform</td></tr>
 *     <tr><td>:cypriot</td><td>Cypriot</td></tr>
 *     <tr><td>:cyrillic</td><td>Cyrillic</td></tr>
 *     <tr><td>:deseret</td><td>Deseret</td></tr>
 *     <tr><td>:devanagari</td><td>Devanagari</td></tr>
 *     <tr><td>:egyptian_hieroglyphs</td><td>Egyptian Hieroglpyhs</td></tr>
 *     <tr><td>:ethiopic</td><td>Ethiopic</td></tr>
 *     <tr><td>:georgian</td><td>Georgian</td></tr>
 *     <tr><td>:glagolitic</td><td>Glagolitic</td></tr>
 *     <tr><td>:gothic</td><td>Gothic</td></tr>
 *     <tr><td>:greek</td><td>Greek</td></tr>
 *     <tr><td>:gujarati</td><td>Gujarati</td></tr>
 *     <tr><td>:gurmukhi</td><td>Gurmukhi</td></tr>
 *     <tr><td>:han</td><td>Han</td></tr>
 *     <tr><td>:hangul</td><td>Hangul</td></tr>
 *     <tr><td>:hanunoo</td><td>Hanunoo</td></tr>
 *     <tr><td>:hebrew</td><td>Hebrew</td></tr>
 *     <tr><td>:hiragana</td><td>Hiragana</td></tr>
 *     <tr><td>:imperial_aramaic</td><td>Imperial Aramaic</td></tr>
 *     <tr><td>:inherited</td><td>For characters that may be used with multiple
 *     scripts, and that inherit their script from the preceding characters;
 *     these include nonspacing marks, enclosing marks, and the zero-width
 *     joiner/non-joiner characters</td></tr>
 *     <tr><td>:inscriptional_pahlavi</td><td>Inscriptional Pahlavi</td></tr>
 *     <tr><td>:inscriptional_parthian</td><td>Inscriptional Parthian</td></tr>
 *     <tr><td>:javanese</td><td>Javanese</td></tr>
 *     <tr><td>:kaithi</td><td>Kaithi</td></tr>
 *     <tr><td>:kannada</td><td>Kannada</td></tr>
 *     <tr><td>:katakana</td><td>Katakana</td></tr>
 *     <tr><td>:kayah_li</td><td>Kayah Li</td></tr>
 *     <tr><td>:kharoshthi</td><td>Kharoshthi</td></tr>
 *     <tr><td>:khmer</td><td>Khmer</td></tr>
 *     <tr><td>:lao</td><td>Lao</td></tr>
 *     <tr><td>:latin</td><td>Latin</td></tr>
 *     <tr><td>:lepcha</td><td>Lepcha</td></tr>
 *     <tr><td>:limbu</td><td>Limbu</td></tr>
 *     <tr><td>:linear_b</td><td>Linear B</td></tr>
 *     <tr><td>:lisu</td><td>Lisu</td></tr>
 *     <tr><td>:lycian</td><td>Lycian</td></tr>
 *     <tr><td>:lydian</td><td>Lydian</td></tr>
 *     <tr><td>:malayalam</td><td>Malayalam</td></tr>
 *     <tr><td>:mandaic</td><td>Mandaic</td></tr>
 *     <tr><td>:meetei_mayek</td><td>Meetei Mayek</td></tr>
 *     <tr><td>:meroitic_hieroglyphs</td><td>Meroitic Hieroglyphs</td></tr>
 *     <tr><td>:meroitic_cursive</td><td>Meroitic Cursives</td></tr>
 *     <tr><td>:miao</td><td>Miao</td></tr>
 *     <tr><td>:mongolian</td><td>Mongolian</td></tr>
 *     <tr><td>:myanmar</td><td>Myanmar</td></tr>
 *     <tr><td>:new_tai_lue</td><td>New Tai Lue</td></tr>
 *     <tr><td>:nko</td><td>N'Ko</td></tr>
 *     <tr><td>:ogham</td><td>Ogham</td></tr>
 *     <tr><td>:old_italic</td><td>Old Italic</td></tr>
 *     <tr><td>:old_persian</td><td>Old Persian</td></tr>
 *     <tr><td>:old_south_arabian</td><td>Old South Arabian</td></tr>
 *     <tr><td>:old_turkic</td><td>Old Turkic</td></tr>
 *     <tr><td>:ol_chiki</td><td>Ol Chiki</td></tr>
 *     <tr><td>:oriya</td><td>Oriya</td></tr>
 *     <tr><td>:osmanya</td><td>Osmanya</td></tr>
 *     <tr><td>:phags_pa</td><td>Phags-pa</td></tr>
 *     <tr><td>:phoenician</td><td>Phoenician</td></tr>
 *     <tr><td>:rejang</td><td>Rejang</td></tr>
 *     <tr><td>:runic</td><td>Runic</td></tr>
 *     <tr><td>:samaritan</td><td>Samaritan</td></tr>
 *     <tr><td>:saurashtra</td><td>Saurashtra</td></tr>
 *     <tr><td>:sharada</td><td>Sharada</td></tr>
 *     <tr><td>:shavian</td><td>Shavian</td></tr>
 *     <tr><td>:sinhala</td><td>Sinhala</td></tr>
 *     <tr><td>:sora_sompeng</td><td>Sora Sompeng</td></tr>
 *     <tr><td>:sundanese</td><td>Sundanese</td></tr>
 *     <tr><td>:syloti_nagri</td><td>Syloti Nagri</td></tr>
 *     <tr><td>:syriac</td><td>Syriac</td></tr>
 *     <tr><td>:tagalog</td><td>Tagalog</td></tr>
 *     <tr><td>:tagbanwa</td><td>Tagbanwa</td></tr>
 *     <tr><td>:tai_le</td><td>Tai Le</td></tr>
 *     <tr><td>:tai_tham</td><td>Tai Tham</td></tr>
 *     <tr><td>:tai_viet</td><td>Tai Viet</td></tr>
 *     <tr><td>:takri</td><td>Takri</td></tr>
 *     <tr><td>:tamil</td><td>Tamil</td></tr>
 *     <tr><td>:telugu</td><td>Telugu</td></tr>
 *     <tr><td>:thaana</td><td>Thaana</td></tr>
 *     <tr><td>:thai</td><td>Thai</td></tr>
 *     <tr><td>:tibetan</td><td>Tibetan</td></tr>
 *     <tr><td>:tifinagh</td><td>Tifinagh</td></tr>
 *     <tr><td>:ugaritic</td><td>Ugaritic</td></tr>
 *     <tr><td>:unknown</td><td>For not assigned, private-use, non-character, and surrogate code points</td></tr>
 *     <tr><td>:vai</td><td>Vai</td></tr>
 *     <tr><td>:yi</td><td>Yi</td></tr>
 *   </tbody>
 * </table>
 *
 * @raise [ArgumentError] If the receiver contains two characters belonging to
 *   different scripts
 * @raise [ArgumentError] If the receiver contains an incomplete UTF-8 sequence
 * @raise [ArgumentError] If the receiver contains an invalid UTF-8 sequence
 * @return [Symbol]
 * @see http://www.unicode.org/reports/tr24/
 *   Unicode Standard Annex #24 Unicode Script Property */
VALUE
rb_u_string_script(VALUE self)
{
        UnicodeScript current = U_SCRIPT_UNKNOWN;

        const struct rb_u_string *string = RVAL2USTRING(self);

        const char *p = USTRING_STR(string);
        const char *end = USTRING_END(string);
        while (p < end) {
                UnicodeScript script = u_char_script(u_aref_char_validated_n(p, end - p));

                if (current == U_SCRIPT_UNKNOWN)
                        current = script;
                else if (script != current)
                        rb_u_raise(rb_eArgError,
                                   "string consists of more than one script: :%s+, :%s",
                                   rb_id2name(SYM2ID(script_to_symbol(current))),
                                   rb_id2name(SYM2ID(script_to_symbol(script))));

                p = u_next(p);
        }

        return script_to_symbol(current);
}
