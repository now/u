#include "rb_includes.h"

#define SCRIPT2ID(script, symbol) \
        static ID id_##symbol; \
        if (id_##symbol == 0) \
                id_##symbol = rb_intern(#symbol);

static VALUE
script_to_symbol(UnicodeScript script)
{
        SCRIPT2ID(UNICODE_SCRIPT_COMMON, common);
        SCRIPT2ID(UNICODE_SCRIPT_INHERITED, inherited);
        SCRIPT2ID(UNICODE_SCRIPT_ARABIC, arabic);
        SCRIPT2ID(UNICODE_SCRIPT_ARMENIAN, armenian);
        SCRIPT2ID(UNICODE_SCRIPT_BENGALI, bengali);
        SCRIPT2ID(UNICODE_SCRIPT_BOPOMOFO, bopomofo);
        SCRIPT2ID(UNICODE_SCRIPT_CHEROKEE, cherokee);
        SCRIPT2ID(UNICODE_SCRIPT_COPTIC, coptic);
        SCRIPT2ID(UNICODE_SCRIPT_CYRILLIC, cyrillic);
        SCRIPT2ID(UNICODE_SCRIPT_DESERET, deseret);
        SCRIPT2ID(UNICODE_SCRIPT_DEVANAGARI, devanagari);
        SCRIPT2ID(UNICODE_SCRIPT_ETHIOPIC, ethiopic);
        SCRIPT2ID(UNICODE_SCRIPT_GEORGIAN, georgian);
        SCRIPT2ID(UNICODE_SCRIPT_GOTHIC, gothic);
        SCRIPT2ID(UNICODE_SCRIPT_GREEK, greek);
        SCRIPT2ID(UNICODE_SCRIPT_GUJARATI, gujarati);
        SCRIPT2ID(UNICODE_SCRIPT_GURMUKHI, gurmukhi);
        SCRIPT2ID(UNICODE_SCRIPT_HAN, han);
        SCRIPT2ID(UNICODE_SCRIPT_HANGUL, hangul);
        SCRIPT2ID(UNICODE_SCRIPT_HEBREW, hebrew);
        SCRIPT2ID(UNICODE_SCRIPT_HIRAGANA, hiragana);
        SCRIPT2ID(UNICODE_SCRIPT_KANNADA, kannada);
        SCRIPT2ID(UNICODE_SCRIPT_KATAKANA, katakana);
        SCRIPT2ID(UNICODE_SCRIPT_KHMER, khmer);
        SCRIPT2ID(UNICODE_SCRIPT_LAO, lao);
        SCRIPT2ID(UNICODE_SCRIPT_LATIN, latin);
        SCRIPT2ID(UNICODE_SCRIPT_MALAYALAM, malayalam);
        SCRIPT2ID(UNICODE_SCRIPT_MONGOLIAN, mongolian);
        SCRIPT2ID(UNICODE_SCRIPT_MYANMAR, myanmar);
        SCRIPT2ID(UNICODE_SCRIPT_OGHAM, ogham);
        SCRIPT2ID(UNICODE_SCRIPT_OLD_ITALIC, old_italic);
        SCRIPT2ID(UNICODE_SCRIPT_ORIYA, oriya);
        SCRIPT2ID(UNICODE_SCRIPT_RUNIC, runic);
        SCRIPT2ID(UNICODE_SCRIPT_SINHALA, sinhala);
        SCRIPT2ID(UNICODE_SCRIPT_SYRIAC, syriac);
        SCRIPT2ID(UNICODE_SCRIPT_TAMIL, tamil);
        SCRIPT2ID(UNICODE_SCRIPT_TELUGU, telugu);
        SCRIPT2ID(UNICODE_SCRIPT_THAANA, thaana);
        SCRIPT2ID(UNICODE_SCRIPT_THAI, thai);
        SCRIPT2ID(UNICODE_SCRIPT_TIBETAN, tibetan);
        SCRIPT2ID(UNICODE_SCRIPT_CANADIAN_ABORIGINAL, canadian_aboriginal);
        SCRIPT2ID(UNICODE_SCRIPT_YI, yi);
        SCRIPT2ID(UNICODE_SCRIPT_TAGALOG, tagalog);
        SCRIPT2ID(UNICODE_SCRIPT_HANUNOO, hanunoo);
        SCRIPT2ID(UNICODE_SCRIPT_BUHID, buhid);
        SCRIPT2ID(UNICODE_SCRIPT_TAGBANWA, tagbanwa);
        SCRIPT2ID(UNICODE_SCRIPT_BRAILLE, braille);
        SCRIPT2ID(UNICODE_SCRIPT_CYPRIOT, cypriot);
        SCRIPT2ID(UNICODE_SCRIPT_LIMBU, limbu);
        SCRIPT2ID(UNICODE_SCRIPT_OSMANYA, osmanya);
        SCRIPT2ID(UNICODE_SCRIPT_SHAVIAN, shavian);
        SCRIPT2ID(UNICODE_SCRIPT_LINEAR_B, linear_b);
        SCRIPT2ID(UNICODE_SCRIPT_TAI_LE, tai_le);
        SCRIPT2ID(UNICODE_SCRIPT_UGARITIC, ugaritic);
        SCRIPT2ID(UNICODE_SCRIPT_NEW_TAI_LUE, new_tai_lue);
        SCRIPT2ID(UNICODE_SCRIPT_BUGINESE, buginese);
        SCRIPT2ID(UNICODE_SCRIPT_GLAGOLITIC, glagolitic);
        SCRIPT2ID(UNICODE_SCRIPT_TIFINAGH, tifinagh);
        SCRIPT2ID(UNICODE_SCRIPT_SYLOTI_NAGRI, syloti_nagri);
        SCRIPT2ID(UNICODE_SCRIPT_OLD_PERSIAN, old_persian);
        SCRIPT2ID(UNICODE_SCRIPT_KHAROSHTHI, kharoshthi);
        SCRIPT2ID(UNICODE_SCRIPT_UNKNOWN, unknown);
        SCRIPT2ID(UNICODE_SCRIPT_BALINESE, balinese);
        SCRIPT2ID(UNICODE_SCRIPT_CUNEIFORM, cuneiform);
        SCRIPT2ID(UNICODE_SCRIPT_PHOENICIAN, phoenician);
        SCRIPT2ID(UNICODE_SCRIPT_PHAGS_PA, phags_pa);
        SCRIPT2ID(UNICODE_SCRIPT_NKO, nko);
        SCRIPT2ID(UNICODE_SCRIPT_KAYAH_LI, kayah_li);
        SCRIPT2ID(UNICODE_SCRIPT_LEPCHA, lepcha);
        SCRIPT2ID(UNICODE_SCRIPT_REJANG, rejang);
        SCRIPT2ID(UNICODE_SCRIPT_SUNDANESE, sundanese);
        SCRIPT2ID(UNICODE_SCRIPT_SAURASHTRA, saurashtra);
        SCRIPT2ID(UNICODE_SCRIPT_CHAM, cham);
        SCRIPT2ID(UNICODE_SCRIPT_OL_CHIKI, ol_chiki);
        SCRIPT2ID(UNICODE_SCRIPT_VAI, vai);
        SCRIPT2ID(UNICODE_SCRIPT_CARIAN, carian);
        SCRIPT2ID(UNICODE_SCRIPT_LYCIAN, lycian);
        SCRIPT2ID(UNICODE_SCRIPT_LYDIAN, lydian);
        SCRIPT2ID(UNICODE_SCRIPT_AVESTAN, avestan);
        SCRIPT2ID(UNICODE_SCRIPT_BAMUM, bamum);
        SCRIPT2ID(UNICODE_SCRIPT_EGYPTIAN_HIEROGLYPHS, egyptian_hieroglyphs);
        SCRIPT2ID(UNICODE_SCRIPT_IMPERIAL_ARAMAIC, imperial_aramaic);
        SCRIPT2ID(UNICODE_SCRIPT_INSCRIPTIONAL_PAHLAVI, inscriptional_pahlavi);
        SCRIPT2ID(UNICODE_SCRIPT_INSCRIPTIONAL_PARTHIAN, inscriptional_parthian);
        SCRIPT2ID(UNICODE_SCRIPT_JAVANESE, javanese);
        SCRIPT2ID(UNICODE_SCRIPT_KAITHI, kaithi);
        SCRIPT2ID(UNICODE_SCRIPT_LISU, lisu);
        SCRIPT2ID(UNICODE_SCRIPT_MEETEI_MAYEK, meetei_mayek);
        SCRIPT2ID(UNICODE_SCRIPT_OLD_SOUTH_ARABIAN, old_south_arabian);
        SCRIPT2ID(UNICODE_SCRIPT_OLD_TURKIC, old_turkic);
        SCRIPT2ID(UNICODE_SCRIPT_SAMARITAN, samaritan);
        SCRIPT2ID(UNICODE_SCRIPT_TAI_THAM, tai_tham);
        SCRIPT2ID(UNICODE_SCRIPT_TAI_VIET, tai_viet);
        SCRIPT2ID(UNICODE_SCRIPT_BATAK, batak);
        SCRIPT2ID(UNICODE_SCRIPT_BRAHMI, brahmi);
        SCRIPT2ID(UNICODE_SCRIPT_MANDAIC, mandaic);

        switch (script) {
        case UNICODE_SCRIPT_COMMON:
                return ID2SYM(id_common);
        case UNICODE_SCRIPT_INHERITED:
                return ID2SYM(id_inherited);
        case UNICODE_SCRIPT_ARABIC:
                return ID2SYM(id_arabic);
        case UNICODE_SCRIPT_ARMENIAN:
                return ID2SYM(id_armenian);
        case UNICODE_SCRIPT_BENGALI:
                return ID2SYM(id_bengali);
        case UNICODE_SCRIPT_BOPOMOFO:
                return ID2SYM(id_bopomofo);
        case UNICODE_SCRIPT_CHEROKEE:
                return ID2SYM(id_cherokee);
        case UNICODE_SCRIPT_COPTIC:
                return ID2SYM(id_coptic);
        case UNICODE_SCRIPT_CYRILLIC:
                return ID2SYM(id_cyrillic);
        case UNICODE_SCRIPT_DESERET:
                return ID2SYM(id_deseret);
        case UNICODE_SCRIPT_DEVANAGARI:
                return ID2SYM(id_devanagari);
        case UNICODE_SCRIPT_ETHIOPIC:
                return ID2SYM(id_ethiopic);
        case UNICODE_SCRIPT_GEORGIAN:
                return ID2SYM(id_georgian);
        case UNICODE_SCRIPT_GOTHIC:
                return ID2SYM(id_gothic);
        case UNICODE_SCRIPT_GREEK:
                return ID2SYM(id_greek);
        case UNICODE_SCRIPT_GUJARATI:
                return ID2SYM(id_gujarati);
        case UNICODE_SCRIPT_GURMUKHI:
                return ID2SYM(id_gurmukhi);
        case UNICODE_SCRIPT_HAN:
                return ID2SYM(id_han);
        case UNICODE_SCRIPT_HANGUL:
                return ID2SYM(id_hangul);
        case UNICODE_SCRIPT_HEBREW:
                return ID2SYM(id_hebrew);
        case UNICODE_SCRIPT_HIRAGANA:
                return ID2SYM(id_hiragana);
        case UNICODE_SCRIPT_KANNADA:
                return ID2SYM(id_kannada);
        case UNICODE_SCRIPT_KATAKANA:
                return ID2SYM(id_katakana);
        case UNICODE_SCRIPT_KHMER:
                return ID2SYM(id_khmer);
        case UNICODE_SCRIPT_LAO:
                return ID2SYM(id_lao);
        case UNICODE_SCRIPT_LATIN:
                return ID2SYM(id_latin);
        case UNICODE_SCRIPT_MALAYALAM:
                return ID2SYM(id_malayalam);
        case UNICODE_SCRIPT_MONGOLIAN:
                return ID2SYM(id_mongolian);
        case UNICODE_SCRIPT_MYANMAR:
                return ID2SYM(id_myanmar);
        case UNICODE_SCRIPT_OGHAM:
                return ID2SYM(id_ogham);
        case UNICODE_SCRIPT_OLD_ITALIC:
                return ID2SYM(id_old_italic);
        case UNICODE_SCRIPT_ORIYA:
                return ID2SYM(id_oriya);
        case UNICODE_SCRIPT_RUNIC:
                return ID2SYM(id_runic);
        case UNICODE_SCRIPT_SINHALA:
                return ID2SYM(id_sinhala);
        case UNICODE_SCRIPT_SYRIAC:
                return ID2SYM(id_syriac);
        case UNICODE_SCRIPT_TAMIL:
                return ID2SYM(id_tamil);
        case UNICODE_SCRIPT_TELUGU:
                return ID2SYM(id_telugu);
        case UNICODE_SCRIPT_THAANA:
                return ID2SYM(id_thaana);
        case UNICODE_SCRIPT_THAI:
                return ID2SYM(id_thai);
        case UNICODE_SCRIPT_TIBETAN:
                return ID2SYM(id_tibetan);
        case UNICODE_SCRIPT_CANADIAN_ABORIGINAL:
                return ID2SYM(id_canadian_aboriginal);
        case UNICODE_SCRIPT_YI:
                return ID2SYM(id_yi);
        case UNICODE_SCRIPT_TAGALOG:
                return ID2SYM(id_tagalog);
        case UNICODE_SCRIPT_HANUNOO:
                return ID2SYM(id_hanunoo);
        case UNICODE_SCRIPT_BUHID:
                return ID2SYM(id_buhid);
        case UNICODE_SCRIPT_TAGBANWA:
                return ID2SYM(id_tagbanwa);
        case UNICODE_SCRIPT_BRAILLE:
                return ID2SYM(id_braille);
        case UNICODE_SCRIPT_CYPRIOT:
                return ID2SYM(id_cypriot);
        case UNICODE_SCRIPT_LIMBU:
                return ID2SYM(id_limbu);
        case UNICODE_SCRIPT_OSMANYA:
                return ID2SYM(id_osmanya);
        case UNICODE_SCRIPT_SHAVIAN:
                return ID2SYM(id_shavian);
        case UNICODE_SCRIPT_LINEAR_B:
                return ID2SYM(id_linear_b);
        case UNICODE_SCRIPT_TAI_LE:
                return ID2SYM(id_tai_le);
        case UNICODE_SCRIPT_UGARITIC:
                return ID2SYM(id_ugaritic);
        case UNICODE_SCRIPT_NEW_TAI_LUE:
                return ID2SYM(id_new_tai_lue);
        case UNICODE_SCRIPT_BUGINESE:
                return ID2SYM(id_buginese);
        case UNICODE_SCRIPT_GLAGOLITIC:
                return ID2SYM(id_glagolitic);
        case UNICODE_SCRIPT_TIFINAGH:
                return ID2SYM(id_tifinagh);
        case UNICODE_SCRIPT_SYLOTI_NAGRI:
                return ID2SYM(id_syloti_nagri);
        case UNICODE_SCRIPT_OLD_PERSIAN:
                return ID2SYM(id_old_persian);
        case UNICODE_SCRIPT_KHAROSHTHI:
                return ID2SYM(id_kharoshthi);
        case UNICODE_SCRIPT_UNKNOWN:
                return ID2SYM(id_unknown);
        case UNICODE_SCRIPT_BALINESE:
                return ID2SYM(id_balinese);
        case UNICODE_SCRIPT_CUNEIFORM:
                return ID2SYM(id_cuneiform);
        case UNICODE_SCRIPT_PHOENICIAN:
                return ID2SYM(id_phoenician);
        case UNICODE_SCRIPT_PHAGS_PA:
                return ID2SYM(id_phags_pa);
        case UNICODE_SCRIPT_NKO:
                return ID2SYM(id_nko);
        case UNICODE_SCRIPT_KAYAH_LI:
                return ID2SYM(id_kayah_li);
        case UNICODE_SCRIPT_LEPCHA:
                return ID2SYM(id_lepcha);
        case UNICODE_SCRIPT_REJANG:
                return ID2SYM(id_rejang);
        case UNICODE_SCRIPT_SUNDANESE:
                return ID2SYM(id_sundanese);
        case UNICODE_SCRIPT_SAURASHTRA:
                return ID2SYM(id_saurashtra);
        case UNICODE_SCRIPT_CHAM:
                return ID2SYM(id_cham);
        case UNICODE_SCRIPT_OL_CHIKI:
                return ID2SYM(id_ol_chiki);
        case UNICODE_SCRIPT_VAI:
                return ID2SYM(id_vai);
        case UNICODE_SCRIPT_CARIAN:
                return ID2SYM(id_carian);
        case UNICODE_SCRIPT_LYCIAN:
                return ID2SYM(id_lycian);
        case UNICODE_SCRIPT_LYDIAN:
                return ID2SYM(id_lydian);
        case UNICODE_SCRIPT_AVESTAN:
                return ID2SYM(id_avestan);
        case UNICODE_SCRIPT_BAMUM:
                return ID2SYM(id_bamum);
        case UNICODE_SCRIPT_EGYPTIAN_HIEROGLYPHS:
                return ID2SYM(id_egyptian_hieroglyphs);
        case UNICODE_SCRIPT_IMPERIAL_ARAMAIC:
                return ID2SYM(id_imperial_aramaic);
        case UNICODE_SCRIPT_INSCRIPTIONAL_PAHLAVI:
                return ID2SYM(id_inscriptional_pahlavi);
        case UNICODE_SCRIPT_INSCRIPTIONAL_PARTHIAN:
                return ID2SYM(id_inscriptional_parthian);
        case UNICODE_SCRIPT_JAVANESE:
                return ID2SYM(id_javanese);
        case UNICODE_SCRIPT_KAITHI:
                return ID2SYM(id_kaithi);
        case UNICODE_SCRIPT_LISU:
                return ID2SYM(id_lisu);
        case UNICODE_SCRIPT_MEETEI_MAYEK:
                return ID2SYM(id_meetei_mayek);
        case UNICODE_SCRIPT_OLD_SOUTH_ARABIAN:
                return ID2SYM(id_old_south_arabian);
        case UNICODE_SCRIPT_OLD_TURKIC:
                return ID2SYM(id_old_turkic);
        case UNICODE_SCRIPT_SAMARITAN:
                return ID2SYM(id_samaritan);
        case UNICODE_SCRIPT_TAI_THAM:
                return ID2SYM(id_tai_tham);
        case UNICODE_SCRIPT_TAI_VIET:
                return ID2SYM(id_tai_viet);
        case UNICODE_SCRIPT_BATAK:
                return ID2SYM(id_batak);
        case UNICODE_SCRIPT_BRAHMI:
                return ID2SYM(id_brahmi);
        case UNICODE_SCRIPT_MANDAIC:
                return ID2SYM(id_mandaic);
        default:
                rb_u_raise(rb_eNotImpError, "unknown script: %d", script);
        }
}

/* Determines the script of the characters of this {U::String}.
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
 *     <tr><td>:KATAKANA</td><td>Katakana</td></tr>
 *     <tr><td>:KAYAH_LI</td><td>Kayah Li</td></tr>
 *     <tr><td>:KHAROSHTHI</td><td>Kharoshthi</td></tr>
 *     <tr><td>:KHMER</td><td>Khmer</td></tr>
 *     <tr><td>:LAO</td><td>Lao</td></tr>
 *     <tr><td>:LATIN</td><td>Latin</td></tr>
 *     <tr><td>:lepcha</td><td>Lepcha</td></tr>
 *     <tr><td>:limbu</td><td>Limbu</td></tr>
 *     <tr><td>:linear_b</td><td>Linear B</td></tr>
 *     <tr><td>:lisu</td><td>Lisu</td></tr>
 *     <tr><td>:lycian</td><td>Lycian</td></tr>
 *     <tr><td>:lydian</td><td>Lydian</td></tr>
 *     <tr><td>:malayalam</td><td>Malayalam</td></tr>
 *     <tr><td>:mandaic</td><td>Mandaic</td></tr>
 *     <tr><td>:meetei_mayek</td><td>Meetei Mayek</td></tr>
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
 *     <tr><td>:shavian</td><td>Shavian</td></tr>
 *     <tr><td>:sinhala</td><td>Sinhala</td></tr>
 *     <tr><td>:sundanese</td><td>Sundanese</td></tr>
 *     <tr><td>:syloti_nagri</td><td>Syloti Nagri</td></tr>
 *     <tr><td>:syriac</td><td>Syriac</td></tr>
 *     <tr><td>:tagalog</td><td>Tagalog</td></tr>
 *     <tr><td>:tagbanwa</td><td>Tagbanwa</td></tr>
 *     <tr><td>:tai_le</td><td>Tai Le</td></tr>
 *     <tr><td>:tai_tham</td><td>Tai Tham</td></tr>
 *     <tr><td>:tai_viet</td><td>Tai Viet</td></tr>
 *     <tr><td>:tamil</td><td>Tamil</td></tr>
 *     <tr><td>:telugu</td><td>Telugu</td></tr>
 *     <tr><td>:thaana</td><td>Thaana</td></tr>
 *     <tr><td>:thai</td><td>Thai</td></tr>
 *     <tr><td>:tibetan</td><td>Tibetan</td></tr>
 *     <tr><td>:tifinagh</td><td>Tifinagh</td></tr>
 *     <tr><td>:ugaritic</td><td>Ugaritic</td></tr>
 *     <tr><td>:unknown</td><td>For unassigned, private-use, non-character, and surrogate codepoints</td></tr>
 *     <tr><td>:vai</td><td>Vai</td></tr>
 *     <tr><td>:yi</td><td>Yi</td></tr>
 *   </tbody>
 * </table>
 *
 * @see http://www.unicode.org/reports/tr24/
 *
 * @raise [ArgumentError] If `self` contains two characters belonging to
 *   different scripts
 * @raise [ArgumentError] If `self` contains an incomplete UTF-8 sequence
 * @raise [ArgumentError] If `self` contains an invalid UTF-8 sequence
 * @return [Symbol] The script of the characters of this {U::String} */
VALUE
rb_u_string_script(VALUE self)
{
        UnicodeScript current = UNICODE_SCRIPT_UNKNOWN;

        const UString *string = RVAL2USTRING(self);

        const char *p = USTRING_STR(string);
        const char *end = USTRING_END(string);
        while (p < end) {
                UnicodeScript script = unichar_script(u_aref_char_validated_n(p, end - p));

                if (current == UNICODE_SCRIPT_UNKNOWN)
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
