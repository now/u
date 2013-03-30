# -*- coding: utf-8 -*-

require 'u/build'

class Break
  def initialize(data, line_break, io = $stdout)
    U::Build::Header.new(io) do
      io.puts U::Build::Header::Tables::Split.new(data, 'int8_t', 'break_property'){ |i|
        'U_%s' % Mappings[line_break[i]]
      }
    end
  end

private

  module Mappings
    Mappings = {
      'BK' => 'BREAK_MANDATORY',
      'CR' => 'BREAK_CARRIAGE_RETURN',
      'LF' => 'BREAK_LINE_FEED',
      'CM' => 'BREAK_COMBINING_MARK',
      'SG' => 'BREAK_SURROGATE',
      'ZW' => 'BREAK_ZERO_WIDTH_SPACE',
      'IN' => 'BREAK_INSEPARABLE',
      'GL' => 'BREAK_NON_BREAKING_GLUE',
      'CB' => 'BREAK_CONTINGENT',
      'SP' => 'BREAK_SPACE',
      'BA' => 'BREAK_AFTER',
      'BB' => 'BREAK_BEFORE',
      'B2' => 'BREAK_BEFORE_AND_AFTER',
      'HY' => 'BREAK_HYPHEN',
      'NS' => 'BREAK_NON_STARTER',
      'OP' => 'BREAK_OPEN_PUNCTUATION',
      'CL' => 'BREAK_CLOSE_PUNCTUATION',
      'QU' => 'BREAK_QUOTATION',
      'EX' => 'BREAK_EXCLAMATION',
      'ID' => 'BREAK_IDEOGRAPHIC',
      'NU' => 'BREAK_NUMERIC',
      'IS' => 'BREAK_INFIX_SEPARATOR',
      'SY' => 'BREAK_SYMBOL',
      'AL' => 'BREAK_ALPHABETIC',
      'PR' => 'BREAK_PREFIX',
      'PO' => 'BREAK_POSTFIX',
      'SA' => 'BREAK_COMPLEX_CONTEXT',
      'AI' => 'BREAK_AMBIGUOUS',
      'NL' => 'BREAK_NEXT_LINE',
      'WJ' => 'BREAK_WORD_JOINER',
      'XX' => 'BREAK_UNKNOWN',
      'JL' => 'BREAK_HANGUL_L_JAMO',
      'JV' => 'BREAK_HANGUL_V_JAMO',
      'JT' => 'BREAK_HANGUL_T_JAMO',
      'H2' => 'BREAK_HANGUL_LV_SYLLABLE',
      'H3' => 'BREAK_HANGUL_LVT_SYLLABLE',
      'CP' => 'BREAK_CLOSE_PARENTHESIS',
      'HL' => 'BREAK_HEBREW_LETTER',
      'CJ' => 'BREAK_CONDITIONAL_JAPANESE_STARTER',
      'RI' => 'BREAK_REGIONAL_INDICATOR'
    }.freeze

    class << self
      def [](value)
        Mappings[value] or
          raise 'unknown LineBreak property value: %s; the Unicode standard has changed' %
            value
      end
    end
  end
end

data = Marshal.load(File.open(ARGV[0], 'rb', &:read))
Break.new(data, U::Build::Data::LineBreak.new(data, ARGV[1]))
