#include "rb_includes.h"

static size_t
mirror_loop(const char *string, size_t length, bool use_length, char *result)
{
        size_t n = 0;

        const char *p = string;
        const char *end = p + length;
        while (P_WITHIN_STR(p, end, use_length)) {
                unichar c = u_aref_char(p);
                unichar mirrored;

                if (!unichar_mirror(c, &mirrored))
                        mirrored = c;

                n += unichar_to_u(mirrored, OFFSET_IF(result, n));

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

VALUE
rb_u_string_mirror(VALUE self)
{
        const UString *string = RVAL2USTRING(self);

        size_t length;
        char *mirrored = u_mirror_n(USTRING_STR(string),
                                    USTRING_LENGTH(string),
                                    &length);

        return rb_u_string_new_own(mirrored, length);
}
