# -*- coding: utf-8 -*-

require 'u/build'

class Break
  # TODO: UnicodeData should be able to tell us #last, #last_char_part1_x, and
  # so on without actually forcing us to load all the data.
  def initialize(data, line_break, name, version, io = $stdout)
    # TODO: Defines should be made with a list, but we can’t match formatting
    # quite yet, so wait until we have stable tests.
    U::Build::Header.new(name, io) do
      io.puts <<EOH
#define UNICODE_DATA_VERSION "#{version}"

#define UNICODE_LAST_CHAR #{sprintf('0x%04x', data.last)}

#define UNICODE_MAX_TABLE_INDEX 10000

/*
 * The last code point that should be looked up in break_property_table_part1.
 */
#define UNICODE_LAST_CHAR_PART1 #{data.last_char_part1_x}

/*
 * The first code point that should be looked up in break_property_table_part2.
 */
#define UNICODE_FIRST_CHAR_PART2 0xe0000
EOH

      U::Build::Header::Table.
        new(0, data.last_char_part1_i, data.last, io,
            'static const int8_t break_property_data[][256]',
            "/* U+0000 through U+%s */\nstatic const int16_t break_property_table_part1[%s]" % [data.last_char_part1_X, data.pages_before_e0000],
            "/* U+E0000 through U+%04X */\nstatic const int16_t break_property_table_part2[768]" % data.last) do |i|
        Mappings[line_break[i]]
      end
    end
  end

private

  Mappings = {
    'BK' => 'UNICODE_BREAK_MANDATORY',
    'CR' => 'UNICODE_BREAK_CARRIAGE_RETURN',
    'LF' => 'UNICODE_BREAK_LINE_FEED',
    'CM' => 'UNICODE_BREAK_COMBINING_MARK',
    'SG' => 'UNICODE_BREAK_SURROGATE',
    'ZW' => 'UNICODE_BREAK_ZERO_WIDTH_SPACE',
    'IN' => 'UNICODE_BREAK_INSEPARABLE',
    'GL' => 'UNICODE_BREAK_NON_BREAKING_GLUE',
    'CB' => 'UNICODE_BREAK_CONTINGENT',
    'SP' => 'UNICODE_BREAK_SPACE',
    'BA' => 'UNICODE_BREAK_AFTER',
    'BB' => 'UNICODE_BREAK_BEFORE',
    'B2' => 'UNICODE_BREAK_BEFORE_AND_AFTER',
    'HY' => 'UNICODE_BREAK_HYPHEN',
    'NS' => 'UNICODE_BREAK_NON_STARTER',
    'OP' => 'UNICODE_BREAK_OPEN_PUNCTUATION',
    'CL' => 'UNICODE_BREAK_CLOSE_PUNCTUATION',
    'QU' => 'UNICODE_BREAK_QUOTATION',
    'EX' => 'UNICODE_BREAK_EXCLAMATION',
    'ID' => 'UNICODE_BREAK_IDEOGRAPHIC',
    'NU' => 'UNICODE_BREAK_NUMERIC',
    'IS' => 'UNICODE_BREAK_INFIX_SEPARATOR',
    'SY' => 'UNICODE_BREAK_SYMBOL',
    'AL' => 'UNICODE_BREAK_ALPHABETIC',
    'PR' => 'UNICODE_BREAK_PREFIX',
    'PO' => 'UNICODE_BREAK_POSTFIX',
    'SA' => 'UNICODE_BREAK_COMPLEX_CONTEXT',
    'AI' => 'UNICODE_BREAK_AMBIGUOUS',
    'NL' => 'UNICODE_BREAK_NEXT_LINE',
    'WJ' => 'UNICODE_BREAK_WORD_JOINER',
    'XX' => 'UNICODE_BREAK_UNKNOWN',
    'JL' => 'UNICODE_BREAK_HANGUL_L_JAMO',
    'JV' => 'UNICODE_BREAK_HANGUL_V_JAMO',
    'JT' => 'UNICODE_BREAK_HANGUL_T_JAMO',
    'H2' => 'UNICODE_BREAK_HANGUL_LV_SYLLABLE',
    'H3' => 'UNICODE_BREAK_HANGUL_LVT_SYLLABLE'
  }.freeze
end

data = U::Build::Data::Unicode.new(ARGV[0])
Break.new(data, U::Build::Data::LineBreak.new(data, ARGV[1]), ARGV[2], ARGV[3])
