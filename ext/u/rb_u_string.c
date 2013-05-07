/* -*- coding: utf-8 -*- */

#include <ruby.h>
#ifdef HAVE_RUBY_ENCODING_H
#  include <ruby/encoding.h>
#endif
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>
#include "u.h"
#include "private.h"
#include "rb_private.h"
#include "rb_u_string.h"

VALUE rb_cUString;

static void
rb_u_string_mark(const struct rb_u_string *string)
{
        rb_gc_mark(string->rb);
}

static void
rb_u_string_free(struct rb_u_string *string)
{
        free((char *)string->c);
        free(string);
}

static VALUE
rb_u_string_set_rb(VALUE self, VALUE rb)
{
        struct rb_u_string *string = RVAL2USTRING(self);
        if (NIL_P(rb)) {
                string->rb = rb;
                return self;
        }
#ifdef HAVE_RUBY_ENCODING_H
        rb = rb_str_encode(rb, rb_enc_from_encoding(rb_utf8_encoding()), 0, Qnil);
#endif
        string->rb = rb_str_freeze(rb);
        OBJ_INFECT(self, string->rb);
        return self;
}

static VALUE
rb_u_string_create(VALUE rb, const char *str, long length)
{
        struct rb_u_string *string = ALLOC(struct rb_u_string);
        string->rb = Qnil;
        string->c = str;
        string->length = length;
        return rb_u_string_set_rb(USTRING2RVAL(string), rb);
}

static VALUE
rb_u_string_alloc(UNUSED(VALUE klass))
{
        return rb_u_string_create(Qnil, NULL, 0);
}

VALUE
rb_u_string_new_uninfected(const char *str, long length)
{
        return rb_u_string_new_c(Qnil, str, length);
}

VALUE
rb_u_string_new_uninfected_own(const char *str, long length)
{
        return rb_u_string_new_c_own(Qnil, str, length);
}

VALUE
rb_u_string_new_c(VALUE self, const char *str, long length)
{
        char *copy = ALLOC_N(char, length + 1);
        MEMCPY(copy, str, char, length);
        copy[length] = '\0';
        return rb_u_string_new_c_own(self, copy, length);
}

VALUE
rb_u_string_new_c_own(VALUE self, const char *str, long length)
{
        VALUE result = rb_u_string_create(Qnil, str, length);
        OBJ_INFECT(result, self);
        return result;
}

VALUE
rb_u_string_new_rb(VALUE str)
{
        return rb_u_string_create(str, NULL, 0);
}

VALUE
rb_u_string_new_subsequence(VALUE self, long begin, long length)
{
        const struct rb_u_string *string = RVAL2USTRING(self);
        return rb_u_string_new_c(self, USTRING_STR(string) + begin, length);
}

VALUE
rb_u_string_new_empty(VALUE self)
{
        return rb_u_string_new_subsequence(self, 0, 0);
}

VALUE
rb_u_string_check_type(VALUE str)
{
        if (RTEST(rb_obj_is_kind_of(str, rb_cUString)))
                return str;

        return rb_check_string_type(str);
}

VALUE
rb_u_string_validate_type(VALUE str)
{
        VALUE converted = rb_u_string_check_type(str);

        if (NIL_P(converted))
                rb_u_raise(rb_eTypeError,
                           "type mismatch: %s given",
                           rb_obj_classname(str));

        return converted;
}

VALUE
rb_u_string_object_as_string(VALUE object)
{
        if (TYPE(object) == T_STRING || RTEST(rb_obj_is_kind_of(object, rb_cUString)))
                return object;

        static ID id_to_s;
        if (id_to_s == 0)
                id_to_s = rb_intern("to_s");

        VALUE str = rb_funcall(object, id_to_s, 0);
        if (TYPE(str) != T_STRING)
                return rb_any_to_s(object);

        if (OBJ_TAINTED(object))
                OBJ_TAINT(str);

        return str;
}

/* @!visibility public
 * @overload new(string = nil)
 *
 *   Sets up a U::String wrapping STRING after encoding it as UTF-8 and
 *   freezing it.
 *
 *   @param [String, nil] string
 */
static VALUE
rb_u_string_initialize(int argc, VALUE *argv, VALUE self)
{
        VALUE rb;

        rb_scan_args(argc, argv, "01", &rb);
        if (!NIL_P(rb)) {
                StringValue(rb);
                rb_u_string_set_rb(self, rb);
        }

        return Qnil;
}

static VALUE
rb_u_string_initialize_copy(VALUE self, VALUE rboriginal)
{
        struct rb_u_string *string = RVAL2USTRING(self);
        const struct rb_u_string *original = RVAL2USTRING(rboriginal);

        if (string == original)
                return self;

        string->rb = original->rb;
        string->c = original->c;
        string->length = original->length;

        OBJ_INFECT(self, rboriginal);

        return self;
}

VALUE
rb_u_string_dup(VALUE self)
{
        const struct rb_u_string *string = RVAL2USTRING(self);

        VALUE result = rb_u_string_create(string->rb, string->c, string->length);
        OBJ_INFECT(result, self);
        return result;
}

#include <errno.h>

static VALUE
rb_u_string_recode(VALUE self, VALUE codeset)
{
        const struct rb_u_string *string = RVAL2USTRING(self);
        const char *cs = StringValuePtr(codeset);
        errno = 0;
        size_t n = u_recode(NULL, 0, USTRING_STR(string), USTRING_LENGTH(string), cs);
        if (errno != 0)
                rb_u_raise_errno(errno, "can’t recode");
        char *recoded = ALLOC_N(char, n + 1);
        u_recode(recoded, n + 1, USTRING_STR(string), USTRING_LENGTH(string), cs);
        return rb_str_new(recoded, n);
}

/* Document-class: U::String
 *
 * A U::String is a sequence of zero or more Unicode characters encoded as
 * UTF-8.  It’s interface is an extension of that of Ruby’s built-in String
 * class that provides better Unicode support, as it handles things such as
 * casing, width, collation, and various other Unicode properties that Ruby’s
 * built-in String class simply doesn’t bother itself with.  It also provides
 * “backwards compatibility” with Ruby 1.8.7 so that you can use Unicode
 * without upgrading to Ruby 2.0 (which you probably should do, though).
 *
 * It differs from Ruby’s built-in String class in one other very important way
 * in that it doesn’t provide any way to change an existing object.  That is, a
 * U::String is a value object.
 *
 * A U::String is most easily created from a String by calling {String#u}.
 * Most U::String methods that return a stringy result will return a U::String,
 * so you only have to do that once.  You can get back a String by calling
 * {U::String#to_str}.
 *
 * Validation of a U::String’s content isn’t performed until any access to it
 * is made, at which time an ArgumentError will be raised if it isn’t valid.
 *
 * U::String has a lot of methods defined upon it, so let’s break them up into
 * categories to get a proper overview of what’s possible to do with one.
 * Let’s begin with the interrogators.  There are three kinds of interrogators,
 * validity-checking ones, property-checking ones, and content-matching ones.
 *
 * The validity-checking interrogator is {#valid_encoding?}, which makes sure
 * that the UTF-8 sequence itself is valid.
 *
 * The property-checking interrogators are {#alnum?}, {#alpha?},
 * {#ascii_only?}, {#assigned?}, {#case_ignorable?}, {#cased?}, {#cntrl?},
 * {#defined?}, {#digit?}, {#folded?}, {#graph?}, {#lower?}, {#newline?},
 * {#print?}, {#punct?}, {#soft_dotted?}, {#space?}, {#title?}, {#upper?},
 * {#valid?}, {#wide?}, {#wide_cjk?}, {#xdigit?}, and {#zero_width?}.  These
 * interrogators check the corresponding Unicode property of each characters in
 * the U::String and if all characters have this property, they’ll return true.
 *
 * A very close relative to the property-checking interrogators is
 * {#normalized?}, which checks whether the receiver has been normalized,
 * optionally to a specific normaliation form.
 *
 * The content-matching interrogators are {#==}, {#===}, {#=~}, {#match},
 * {#empty?}, {#end_with?}, {#eql?}, {#include?}, {#index}, {#rindex}, and
 * {#start_with?}.  These interrogators check that a substring of the U::String
 * matches another string or Regexp and either return a Boolean result, and
 * index into the U::String where the match begins or MatchData for full
 * matching information.
 *
 * Related to the content-matching interrogators are {#<=>}, {#casecmp}, and
 * {#collation_key}, all of which compare a U::String against another for
 * ordering.
 *
 * Related to the property-checking interrogators are
 * {#canonical_combining_class}, {#general_category}, {#grapheme_break},
 * {#line_break}, {#script}, and {#word_break}, which return the value of the
 * Unicode property in question, the general category being the one often
 * interrogated.
 *
 * There are a couple of other “interrogators” in {#bytesize}, {#length},
 * {#size}, {#width} that return integer properties of the U::String as a
 * whole, where #length and #width are probably the most useful.
 *
 * Beyond interrogators there are quite a few methods for iterating over the
 * content of a U::String, each viewing it in its own way: {#each_byte},
 * {#each_char}, {#each_codepoint}, {#each_grapheme_cluster}, {#each_line}, and
 * {#each_word}.  They all have respective methods ({#bytes}, {#chars},
 * {#codepoints}, {#grapheme_clusters}, {#lines}, {#words}) that return an
 * Array instead of yielding each result.
 *
 * Quite a few methods are devoted to extracting a substring of a U::String,
 * namely {#[]}, {#slice}, {#byteslice}, {#chomp}, {#chop}, {#chr}, {#getbyte},
 * {#lstrip}, {#ord}, {#rstrip}, {#strip}.
 *
 * There are a few methods for case-shifting: {#downcase}, {#foldcase},
 * {#titlecase}, and {#upcase}.  Then there’s {#mirror}, {#normalize}, and
 * {#reverse} that alter the string in other ways.
 *
 * The methods {#center}, {#ljust}, and {#rjust} pad a U::String to make it a
 * certain number of cells wide.
 *
 * Then there’s a couple of methods that are more related in the arguments they
 * take than in function: {#count}, {#delete}, {#squeeze}, {#tr}, and {#tr_s}.
 * These methods all take specifications of character/code point ranges that
 * should be counted, deleted, squeezed, and translated (plus squeezed).
 *
 * Deconstructing a U::String can be done with {#partition} and {#rpartition},
 * which splits it around a divider, {#scan}, which extracts matches to a
 * pattern, {#split}, which splits it on a divider.
 *
 * Substitution of all matches to a pattern can be made with {#gsub} and of the
 * first match to a pattern with {#sub}.
 *
 * Creating larger U::Strings from smaller ones is done with {#+}, which
 * concatenates two of them, and {#*}, which concatenates a U::String to itself
 * a number of times.
 *
 * A U::String can also be used as a specification as to how to format a number
 * of values via {#%} (and its alias {#format}) into a new U::String, much like
 * snprintf(3) in C.
 *
 * The content of a U::String can be {#dump}ed and {#inspect}ed to make it
 * reader-friendly, but also debugger-friendly.
 *
 * Finally, a U::String has a few methods to turn its content into other
 * values: {#hash}, which turns it into a hash value to be used for hashing,
 * {#hex}, {#oct}, {#to_i}, which turn it into a Integer, {#to_str}, {#to_s},
 * {#b}, which turn it into a String, and {#to_sym} (and its alias {#intern}),
 * which turns it into a Symbol.
 *
 * Note that some methods defined on String are missing.  #Capitalize doesn’t
 * exist, as capitalization isn’t a Unicode concept.  #Sum doesn’t exist, as a
 * U::String generally doesn’t contain content that you need a checksum of.
 * \#Crypt doesn’t exist for similar reasons.  #Swapcase isn’t useful on a
 * String and it certainly isn’t useful in a Unicode context.  As a U::String
 * doesn’t contain arbitrary data, #unpack is left to String.  #Next/#succ
 * would perhaps be implementable, but haven’t, as a satisfactory
 * implementation hasn’t been thought of. */
void
Init_u_string(VALUE mU)
{
        rb_cUString = rb_define_class_under(mU, "String", rb_cData);

        rb_include_module(rb_cUString, rb_mComparable);

        rb_define_alloc_func(rb_cUString, rb_u_string_alloc);
        rb_define_private_method(rb_cUString, "initialize", rb_u_string_initialize, -1);
        rb_define_private_method(rb_cUString, "initialize_copy", rb_u_string_initialize_copy, 1);

        rb_define_method(rb_cUString, "valid_encoding?", rb_u_string_valid_encoding, 0); /* in ext/u/rb_u_string_valid_encoding.c */

        rb_define_method(rb_cUString, "alnum?", rb_u_string_alnum, 0); /* in ext/u/rb_u_string_alnum.c */
        rb_define_method(rb_cUString, "alpha?", rb_u_string_alpha, 0); /* in ext/u/rb_u_string_alpha.c */
        rb_define_method(rb_cUString, "ascii_only?", rb_u_string_ascii_only, 0); /* in ext/u/rb_u_string_ascii_only.c */
        rb_define_method(rb_cUString, "assigned?", rb_u_string_assigned, 0); /* in ext/u/rb_u_string_assigned.c */
        rb_define_method(rb_cUString, "case_ignorable?", rb_u_string_case_ignorable, 0); /* in ext/u/rb_u_string_case_ignorable.c */
        rb_define_method(rb_cUString, "cased?", rb_u_string_cased, 0); /* in ext/u/rb_u_string_cased.c */
        rb_define_method(rb_cUString, "cntrl?", rb_u_string_cntrl, 0); /* in ext/u/rb_u_string_cntrl.c */
        rb_define_method(rb_cUString, "defined?", rb_u_string_defined, 0); /* in ext/u/rb_u_string_defined.c */
        rb_define_method(rb_cUString, "digit?", rb_u_string_digit, 0); /* in ext/u/rb_u_string_digit.c */
        rb_define_method(rb_cUString, "folded?", rb_u_string_folded, -1); /* in ext/u/rb_u_string_folded.c */
        rb_define_method(rb_cUString, "graph?", rb_u_string_graph, 0); /* in ext/u/rb_u_string_graph.c */
        rb_define_method(rb_cUString, "lower?", rb_u_string_lower, -1); /* in ext/u/rb_u_string_lower.c */
        rb_define_method(rb_cUString, "newline?", rb_u_string_newline, 0); /* in ext/u/rb_u_string_newline.c */
        rb_define_method(rb_cUString, "print?", rb_u_string_print, 0); /* in ext/u/rb_u_string_print.c */
        rb_define_method(rb_cUString, "punct?", rb_u_string_punct, 0); /* in ext/u/rb_u_string_punct.c */
        rb_define_method(rb_cUString, "soft_dotted?", rb_u_string_soft_dotted, 0); /* in ext/u/rb_u_string_soft_dotted.c */
        rb_define_method(rb_cUString, "space?", rb_u_string_space, 0); /* in ext/u/rb_u_string_space.c */
        rb_define_method(rb_cUString, "title?", rb_u_string_title, 0); /* in ext/u/rb_u_string_title.c */
        rb_define_method(rb_cUString, "upper?", rb_u_string_upper, -1); /* in ext/u/rb_u_string_upper.c */
        rb_define_method(rb_cUString, "valid?", rb_u_string_valid, 0); /* in ext/u/rb_u_string_valid.c */
        rb_define_method(rb_cUString, "wide?", rb_u_string_wide, 0); /* in ext/u/rb_u_string_wide.c */
        rb_define_method(rb_cUString, "wide_cjk?", rb_u_string_wide_cjk, 0); /* in ext/u/rb_u_string_wide_cjk.c */
        rb_define_method(rb_cUString, "xdigit?", rb_u_string_xdigit, 0); /* in ext/u/rb_u_string_xdigit.c */
        rb_define_method(rb_cUString, "zero_width?", rb_u_string_zero_width, 0); /* in ext/u/rb_u_string_zero_width.c */

        rb_define_method(rb_cUString, "normalized?", rb_u_string_normalized, -1); /* in ext/u/rb_u_string_normalized.c */

        rb_define_method(rb_cUString, "==", rb_u_string_equal, 1); /* in ext/u/rb_u_string_equal.c */
        rb_define_alias(rb_cUString, "===", "==");
        rb_define_method(rb_cUString, "=~", rb_u_string_match, 1); /* in ext/u/rb_u_string_match.c */
        rb_define_method(rb_cUString, "match", rb_u_string_match_m, -1); /* in ext/u/rb_u_string_match.c */
        rb_define_method(rb_cUString, "empty?", rb_u_string_empty, 0); /* in ext/u/rb_u_string_empty.c */
        rb_define_method(rb_cUString, "end_with?", rb_u_string_end_with, -1); /* in ext/u/rb_u_string_end_with.c */
        rb_define_method(rb_cUString, "eql?", rb_u_string_eql, 1); /* in ext/u/rb_u_string_eql.c */
        rb_define_method(rb_cUString, "include?", rb_u_string_include, 1); /* in ext/u/rb_u_string_include.c */
        rb_define_method(rb_cUString, "index", rb_u_string_index_m, -1); /* in ext/u/rb_u_string_index.c */
        rb_define_method(rb_cUString, "rindex", rb_u_string_rindex_m, -1); /* in ext/u/rb_u_string_rindex.c */
        rb_define_method(rb_cUString, "start_with?", rb_u_string_start_with, -1); /* in ext/u/rb_u_string_start_with.c */

        rb_define_method(rb_cUString, "<=>", rb_u_string_collate, -1); /* in ext/u/rb_u_string_collate.c */
        rb_define_method(rb_cUString, "casecmp", rb_u_string_casecmp, -1); /* in ext/u/rb_u_string_casecmp.c */
        rb_define_method(rb_cUString, "collation_key", rb_u_string_collation_key, -1); /* in ext/u/rb_u_string_collation_key.c */

        rb_define_method(rb_cUString, "canonical_combining_class", rb_u_string_canonical_combining_class, 0); /* in ext/u/rb_u_string_canonical_combining_class.c */
        rb_define_method(rb_cUString, "general_category", rb_u_string_general_category, 0); /* in ext/u/rb_u_string_general_category.c */
        rb_define_method(rb_cUString, "grapheme_break", rb_u_string_grapheme_break, 0); /* in ext/u/rb_u_string_grapheme_break.c */
        rb_define_method(rb_cUString, "line_break", rb_u_string_line_break, 0); /* in ext/u/rb_u_string_line_break.c */
        rb_define_method(rb_cUString, "script", rb_u_string_script, 0); /* in ext/u/rb_u_string_script.c */
        rb_define_method(rb_cUString, "word_break", rb_u_string_word_break, 0); /* in ext/u/rb_u_string_word_break.c */

        rb_define_method(rb_cUString, "bytesize", rb_u_string_bytesize, 0); /* in ext/u/rb_u_string_bytesize.c */
        rb_define_method(rb_cUString, "length", rb_u_string_length, 0); /* in ext/u/rb_u_string_length.c */
        rb_define_alias(rb_cUString, "size", "length");
        rb_define_method(rb_cUString, "width", rb_u_string_width, 0); /* in ext/u/rb_u_string_width.c */

        rb_define_method(rb_cUString, "each_byte", rb_u_string_each_byte, 0); /* in ext/u/rb_u_string_each_byte.c */
        rb_define_method(rb_cUString, "bytes", rb_u_string_bytes, 0); /* in ext/u/rb_u_string_each_byte.c */
        rb_define_method(rb_cUString, "each_char", rb_u_string_each_char, 0); /* in ext/u/rb_u_string_each_char.c */
        rb_define_method(rb_cUString, "chars", rb_u_string_chars, 0); /* in ext/u/rb_u_string_each_char.c */
        rb_define_method(rb_cUString, "each_codepoint", rb_u_string_each_codepoint, 0); /* in ext/u/rb_u_string_each_codepoint.c */
        rb_define_method(rb_cUString, "codepoints", rb_u_string_codepoints, 0); /* in ext/u/rb_u_string_each_codepoint.c */
        rb_define_method(rb_cUString, "each_grapheme_cluster", rb_u_string_each_grapheme_cluster, 0); /* in ext/u/rb_u_string_each_grapheme_cluster.c */
        rb_define_alias(rb_cUString, "grapheme_clusters", "each_grapheme_cluster");
        rb_define_method(rb_cUString, "each_line", rb_u_string_each_line, -1); /* in ext/u/rb_u_string_each_line.c */
        rb_define_method(rb_cUString, "lines", rb_u_string_lines, -1); /* in ext/u/rb_u_string_each_line.c */
        rb_define_method(rb_cUString, "each_word", rb_u_string_each_word, 0); /* in ext/u/rb_u_string_each_word.c */
        rb_define_alias(rb_cUString, "words", "each_word");

        rb_define_method(rb_cUString, "[]", rb_u_string_aref_m, -1); /* in ext/u/rb_u_string_aref.c */
        rb_define_alias(rb_cUString, "slice", "[]");
        rb_define_method(rb_cUString, "byteslice", rb_u_string_byteslice_m, -1); /* in ext/u/rb_u_string_byteslice.c */
        rb_define_method(rb_cUString, "chomp", rb_u_string_chomp, -1); /* in ext/u/rb_u_string_chomp.c */
        rb_define_method(rb_cUString, "chop", rb_u_string_chop, 0); /* in ext/u/rb_u_string_chop.c */
        rb_define_method(rb_cUString, "chr", rb_u_string_chr, 0); /* in ext/u/rb_u_string_chr.c */
        rb_define_method(rb_cUString, "getbyte", rb_u_string_getbyte, 1); /* in ext/u/rb_u_string_getbyte.c */
        rb_define_method(rb_cUString, "lstrip", rb_u_string_lstrip, 0); /* in ext/u/rb_u_string_lstrip.c */
        rb_define_method(rb_cUString, "ord", rb_u_string_ord, 0); /* in ext/u/rb_u_string_ord.c */
        rb_define_method(rb_cUString, "rstrip", rb_u_string_rstrip, 0); /* in ext/u/rb_u_string_rstrip.c */
        rb_define_method(rb_cUString, "strip", rb_u_string_strip, 0); /* in ext/u/rb_u_string_strip.c */

        rb_define_method(rb_cUString, "downcase", rb_u_string_downcase, -1); /* in ext/u/rb_u_string_downcase.c */
        rb_define_method(rb_cUString, "foldcase", rb_u_string_foldcase, -1); /* in ext/u/rb_u_string_foldcase.c */
        rb_define_method(rb_cUString, "titlecase", rb_u_string_titlecase, -1); /* in ext/u/rb_u_string_titlecase.c */
        rb_define_method(rb_cUString, "upcase", rb_u_string_upcase, -1); /* in ext/u/rb_u_string_upcase.c */

        rb_define_method(rb_cUString, "mirror", rb_u_string_mirror, 0); /* in ext/u/rb_u_string_mirror.c */
        rb_define_method(rb_cUString, "normalize", rb_u_string_normalize, -1); /* in ext/u/rb_u_string_normalize.c */
        rb_define_method(rb_cUString, "reverse", rb_u_string_reverse, 0); /* in ext/u/rb_u_string_reverse.c */

        rb_define_method(rb_cUString, "center", rb_u_string_center, -1); /* in ext/u/rb_u_string_justify.c */
        rb_define_method(rb_cUString, "ljust", rb_u_string_ljust, -1); /* in ext/u/rb_u_string_justify.c */
        rb_define_method(rb_cUString, "rjust", rb_u_string_rjust, -1); /* in ext/u/rb_u_string_justify.c */

        rb_define_method(rb_cUString, "count", rb_u_string_count, -1); /* in ext/u/rb_u_string_count.c */
        rb_define_method(rb_cUString, "delete", rb_u_string_delete, -1); /* in ext/u/rb_u_string_delete.c */
        rb_define_method(rb_cUString, "squeeze", rb_u_string_squeeze, -1); /* in ext/u/rb_u_string_squeeze.c */
        rb_define_method(rb_cUString, "tr", rb_u_string_tr, 2); /* in ext/u/rb_u_string_tr.c */
        rb_define_method(rb_cUString, "tr_s", rb_u_string_tr_s, 2); /* in ext/u/rb_u_string_tr.c */

        rb_define_method(rb_cUString, "partition", rb_u_string_partition, 1); /* in ext/u/rb_u_string_partition.c */
        rb_define_method(rb_cUString, "rpartition", rb_u_string_rpartition, 1); /* in ext/u/rb_u_string_rpartition.c */
        rb_define_method(rb_cUString, "scan", rb_u_string_scan, 1); /* in ext/u/rb_u_string_scan.c */
        rb_define_method(rb_cUString, "split", rb_u_string_split_m, -1); /* in ext/u/rb_u_string_split.c */

        rb_define_method(rb_cUString, "gsub", rb_u_string_gsub, -1); /* in ext/u/rb_u_string_gsub.c */
        rb_define_method(rb_cUString, "sub", rb_u_string_sub, -1); /* in ext/u/rb_u_string_sub.c */

        rb_define_method(rb_cUString, "+", rb_u_string_plus, 1); /* in ext/u/rb_u_string_plus.c */
        rb_define_method(rb_cUString, "*", rb_u_string_times, 1); /* in ext/u/rb_u_string_times.c */

        rb_define_method(rb_cUString, "%", rb_u_string_format_m, 1); /* in ext/u/rb_u_string_format.c */
        rb_define_alias(rb_cUString, "format", "%");

        rb_define_method(rb_cUString, "dump", rb_u_string_dump, 0); /* in ext/u/rb_u_string_dump.c */
        rb_define_method(rb_cUString, "inspect", rb_u_string_inspect, 0); /* in ext/u/rb_u_string_inspect.c */

        rb_define_method(rb_cUString, "hash", rb_u_string_hash, 0); /* in ext/u/rb_u_string_hash.c */
        rb_define_method(rb_cUString, "hex", rb_u_string_hex, 0); /* in ext/u/rb_u_string_hex.c */
        rb_define_method(rb_cUString, "oct", rb_u_string_oct, 0); /* in ext/u/rb_u_string_oct.c */
        rb_define_method(rb_cUString, "to_i", rb_u_string_to_i, -1); /* in ext/u/rb_u_string_to_i.c */
        rb_define_method(rb_cUString, "to_str", rb_u_string_to_str, 0); /* in ext/u/rb_u_string_to_str.c */
        rb_define_alias(rb_cUString, "to_s", "to_str");
        rb_define_method(rb_cUString, "b", rb_u_string_b, 0); /* in ext/u/rb_u_string_b.c */
        rb_define_method(rb_cUString, "to_sym", rb_u_string_to_sym, 0); /* in ext/u/rb_u_string_to_sym.c */
        rb_define_alias(rb_cUString, "intern", "to_sym");

        rb_define_method(rb_cUString, "recode", rb_u_string_recode, 1);
}
