#include "rb_includes.h"

static size_t
mirror_loop(const char *string, size_t length, bool use_length, char *result)
{
        size_t n = 0;

        const char *p = string;
        const char *end = p + length;
        while (P_WITHIN_STR(p, end, use_length)) {
                uint32_t c = u_aref_char(p);
                uint32_t mirrored;

                if (!u_char_mirror(c, &mirrored))
                        mirrored = c;

                n += u_char_to_u(mirrored, OFFSET_IF(result, n));

                p = u_next(p);
        }

        return n;
}

static char *
u_mirror_impl(const char *string, size_t length, bool use_length,
              size_t *new_length)
{
        size_t n = mirror_loop(string, length, use_length, NULL);
        char *result = ALLOC_N(char, n + 1);
        mirror_loop(string, length, use_length, result);
        result[n] = '\0';

        if (new_length != NULL)
                *new_length = n;

        return result;
}

static char *
u_mirror_n(const char *string, size_t length, size_t *new_length)
{
        return u_mirror_impl(string, length, true, new_length);
}

/* Returns the mirroring of the receiver, inheriting any taint and untrust.
 *
 * Mirroring is done by replacing characters in the string with their
 * horizontal mirror image, if any, in text that is laid out from right to
 * left.  For example, ‘(’ becomes ‘)’ and ‘)’ becomes ‘(’.
 *
 * @return [U::String]
 * @see http://www.unicode.org/reports/tr9/
 *   Unicode Standard Annex #9: Unicode Bidirectional Algorithm */
VALUE
rb_u_string_mirror(VALUE self)
{
        const UString *string = RVAL2USTRING(self);

        size_t length;
        char *mirrored = u_mirror_n(USTRING_STR(string),
                                    USTRING_LENGTH(string),
                                    &length);

        return rb_u_string_new_c_own(self, mirrored, length);
}
