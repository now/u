# -*- coding: utf-8 -*-

require 'inventory-1.0'

module U
  Version = Inventory.new(1, 0, 2){
    authors{
      author 'Nikolai Weibull', 'now@disu.se'
    }

    homepage 'http://disu.se/software/u-1.0/'

    licenses{
      license 'LGPLv3+',
              'GNU Lesser General Public License, version 3 or later',
              'http://www.gnu.org/licenses/'
    }

    def dependencies
      super + Inventory::Dependencies.new{
        development 'inventory-rake', 1, 6, 0
        development 'inventory-rake-tasks-yard', 1, 4, 0
        development 'lookout', 3, 0, 0
        development 'lookout-rake', 3, 1, 0
        development 'yard', 0, 8, 0
        development 'yard-heuristics', 1, 2, 0
      }
    end

    def extensions
      [Inventory::Extension.new('u'){
         def sources
           %w[attributes.c
              attributes.h
              case.h
              output.h
              private.c
              private.h
              rb_includes.h
              rb_private.c
              rb_private.h
              rb_u.c
              rb_u_buffer.c
              rb_u_buffer.h
              rb_u_re.c
              rb_u_re.h
              rb_u_string.c
              rb_u_string.h
              rb_u_string_alnum.c
              rb_u_string_alpha.c
              rb_u_string_aref.c
              rb_u_string_ascii_only.c
              rb_u_string_assigned.c
              rb_u_string_b.c
              rb_u_string_bytesize.c
              rb_u_string_byteslice.c
              rb_u_string_case_ignorable.c
              rb_u_string_casecmp.c
              rb_u_string_cased.c
              rb_u_string_chomp.c
              rb_u_string_chop.c
              rb_u_string_chr.c
              rb_u_string_cntrl.c
              rb_u_string_collate.c
              rb_u_string_collation_key.c
              rb_u_string_canonical_combining_class.c
              rb_u_string_count.c
              rb_u_string_defined.c
              rb_u_string_delete.c
              rb_u_string_digit.c
              rb_u_string_downcase.c
              rb_u_string_dump.c
              rb_u_string_each_byte.c
              rb_u_string_each_char.c
              rb_u_string_each_codepoint.c
              rb_u_string_each_grapheme_cluster.c
              rb_u_string_each_line.c
              rb_u_string_each_word.c
              rb_u_string_empty.c
              rb_u_string_end_with.c
              rb_u_string_eql.c
              rb_u_string_equal.c
              rb_u_string_foldcase.c
              rb_u_string_folded.c
              rb_u_string_format.c
              rb_u_string_general_category.c
              rb_u_string_getbyte.c
              rb_u_string_graph.c
              rb_u_string_grapheme_break.c
              rb_u_string_gsub.c
              rb_u_string_hash.c
              rb_u_string_hex.c
              rb_u_string_include.c
              rb_u_string_index.c
              rb_u_string_inspect.c
              rb_u_string_internal_tr.c
              rb_u_string_internal_tr.h
              rb_u_string_justify.c
              rb_u_string_length.c
              rb_u_string_line_break.c
              rb_u_string_lower.c
              rb_u_string_lstrip.c
              rb_u_string_match.c
              rb_u_string_mirror.c
              rb_u_string_newline.c
              rb_u_string_normalize.c
              rb_u_string_normalized.c
              rb_u_string_oct.c
              rb_u_string_ord.c
              rb_u_string_partition.c
              rb_u_string_plus.c
              rb_u_string_print.c
              rb_u_string_punct.c
              rb_u_string_reverse.c
              rb_u_string_rindex.c
              rb_u_string_rpartition.c
              rb_u_string_rstrip.c
              rb_u_string_scan.c
              rb_u_string_script.c
              rb_u_string_soft_dotted.c
              rb_u_string_space.c
              rb_u_string_split.c
              rb_u_string_squeeze.c
              rb_u_string_start_with.c
              rb_u_string_strip.c
              rb_u_string_sub.c
              rb_u_string_times.c
              rb_u_string_title.c
              rb_u_string_titlecase.c
              rb_u_string_to_i.c
              rb_u_string_to_inum.c
              rb_u_string_to_inum.h
              rb_u_string_to_str.c
              rb_u_string_to_sym.c
              rb_u_string_tr.c
              rb_u_string_upcase.c
              rb_u_string_upper.c
              rb_u_string_valid.c
              rb_u_string_valid_encoding.c
              rb_u_string_wide.c
              rb_u_string_wide_cjk.c
              rb_u_string_width.c
              rb_u_string_word_break.c
              rb_u_string_xdigit.c
              rb_u_string_zero_width.c
              titled.c
              titled.h
              u.c
              u.h
              u_char_downcase.c
              u_char_canonical_combining_class.c
              u_char_digit_value.c
              u_char_general_category.c
              u_char_grapheme_break.c
              u_char_isalnum.c
              u_char_isalpha.c
              u_char_isassigned.c
              u_char_iscased.c
              u_char_iscaseignorable.c
              u_char_iscntrl.c
              u_char_isdefined.c
              u_char_isdigit.c
              u_char_isgraph.c
              u_char_islower.c
              u_char_isnewline.c
              u_char_isprint.c
              u_char_ispunct.c
              u_char_issoftdotted.c
              u_char_isspace.c
              u_char_isupper.c
              u_char_isvalid.c
              u_char_iswide.c
              u_char_iswide_cjk.c
              u_char_isxdigit.c
              u_char_iszerowidth.c
              u_char_line_break.c
              u_char_mirror.c
              u_char_normalized.c
              u_char_script.c
              u_char_to_u.c
              u_char_upcase.c
              u_char_xdigit_value.c
              u_char_word_break.c
              u_char_width.c
              u_collate.c
              u_collation_key.c
              u_downcase.c
              u_decode.c
              u_foldcase.c
              u_grapheme_clusters.c
              u_has_prefix.c
              u_index.c
              u_is_ascii_only.c
              u_locale.c
              u_locale.h
              u_mirror.c
              u_n_bytes.c
              u_n_chars.c
              u_normalize.c
              u_normalized.c
              u_offset_to_pointer.c
              u_pointer_to_offset.c
              u_recode.c
              u_reverse.c
              u_rindex.c
              u_titlecase.c
              u_upcase.c
              u_width.c
              u_words.c
              yield.h]
         end

         def additional_files
           %w[build/ext/u/data/attributes.rb
              build/ext/u/data/bidi-mirroring.rb
              build/ext/u/data/case-folding.rb
              build/ext/u/data/cased.rb
              build/ext/u/data/canonical-combining-class.rb
              build/ext/u/data/compose.rb
              build/ext/u/data/constants.rb
              build/ext/u/data/decompose.rb
              build/ext/u/data/general-category.rb
              build/ext/u/data/grapheme-word-break.rb
              build/ext/u/data/marshalled.rb
              build/ext/u/data/script.rb
              build/ext/u/data/soft-dotted.rb
              build/ext/u/data/title-table.rb
              build/ext/u/data/wide.rb
              build/lib/u/build.rb
              build/lib/u/build/data.rb
              build/lib/u/build/data/bidimirroring.rb
              build/lib/u/build/data/break.rb
              build/lib/u/build/data/casefolding.rb
              build/lib/u/build/data/compositionexclusions.rb
              build/lib/u/build/data/derivedeastasianwidth.rb
              build/lib/u/build/data/file.rb
              build/lib/u/build/data/linebreak.rb
              build/lib/u/build/data/proplist.rb
              build/lib/u/build/data/scripts.rb
              build/lib/u/build/data/specialcasing.rb
              build/lib/u/build/data/unicode.rb
              build/lib/u/build/data/unicode/entry.rb
              build/lib/u/build/data/unicode/entry/decomposition.rb
              build/lib/u/build/data/unicode/points.rb
              build/lib/u/build/header.rb
              build/lib/u/build/header/table.rb
              build/lib/u/build/header/table/row.rb
              build/lib/u/build/header/tables.rb
              build/lib/u/build/header/tables/intervals.rb
              build/lib/u/build/header/tables/split.rb
              build/lib/u/build/header/tables/split/data.rb
              build/lib/u/build/header/tables/split/part1.rb
              build/lib/u/build/header/tables/split/part2.rb
              build/lib/u/build/header/tables/split/row.rb
              build/lib/u/build/header/tables/split/rows.rb
              ext/u/data/attributes.h
              ext/u/data/bidi-mirroring.h
              ext/u/data/case-folding.h
              ext/u/data/cased.h
              ext/u/data/canonical-combining-class.h
              ext/u/data/compose.h
              ext/u/data/constants.h
              ext/u/data/decompose.h
              ext/u/data/general-category.h
              ext/u/data/grapheme-break.h
              ext/u/data/line-break.h
              ext/u/data/normalization-quick-check.h
              ext/u/data/script.h
              ext/u/data/soft-dotted.h
              ext/u/data/title-table.h
              ext/u/data/types.h
              ext/u/data/wide-cjk.h
              ext/u/data/wide.h
              ext/u/data/word-break.h]
         end
       }]
    end

    def package_libs
      %w[buffer.rb
         string.rb]
    end

    def additional_unit_tests
      %w[case.rb
         foldcase.rb
         graphemebreak.rb
         wordbreak.rb]
    end

    def additional_files
      %w[build/test/unit/break.rb
         build/test/unit/case.rb
         build/test/unit/foldcase.rb
         build/test/unit/normalize.rb
         test/unit/normalize.rb]
    end
  }
end
