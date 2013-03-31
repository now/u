# -*- coding: utf-8 -*-

require 'u/build'

class Break
  def initialize(data, line_break, io = $stdout)
    U::Build::Header.new(io) do
      io.puts U::Build::Header::Tables::Split.new(data, 'int8_t', 'line_break_property'){ |i|
        'U_LINE_BREAK_%s' % Mappings[line_break[i]]
      }
    end
  end

private

  module Mappings
    Mappings = {
      'BK' => 'MANDATORY',
      'CR' => 'CARRIAGE_RETURN',
      'LF' => 'LINE_FEED',
      'CM' => 'COMBINING_MARK',
      'NL' => 'NEXT_LINE',
      'SG' => 'SURROGATE',
      'WJ' => 'WORD_JOINER',
      'ZW' => 'ZERO_WIDTH_SPACE',
      'GL' => 'NON_BREAKING_GLUE',
      'SP' => 'SPACE',
      'B2' => 'BREAK_OPPORTUNITY_BEFORE_AND_AFTER',
      'BA' => 'BREAK_AFTER',
      'BB' => 'BREAK_BEFORE',
      'HY' => 'HYPHEN',
      'CB' => 'CONTINGENT_BREAK_OPPORTUNITY',
      'CL' => 'CLOSE_PUNCTUATION',
      'CP' => 'CLOSE_PARENTHESIS',
      'EX' => 'EXCLAMATION_INTERROGATION',
      'IN' => 'INSEPARABLE',
      'NS' => 'NONSTARTER',
      'OP' => 'OPEN_PUNCTUATION',
      'QU' => 'QUOTATION',
      'IS' => 'INFIX_NUMERIC_SEPARATOR',
      'NU' => 'NUMERIC',
      'PO' => 'POSTFIX_NUMERIC',
      'PR' => 'PREFIX_NUMERIC',
      'SY' => 'SYMBOLS_ALLOWING_BREAK_AFTER',
      'AI' => 'AMBIGUOUS',
      'AL' => 'ALPHABETIC',
      'CJ' => 'CONDITIONAL_JAPANESE_STARTER',
      'H2' => 'HANGUL_LV_SYLLABLE',
      'H3' => 'HANGUL_LVT_SYLLABLE',
      'HL' => 'HEBREW_LETTER',
      'ID' => 'IDEOGRAPHIC',
      'JL' => 'HANGUL_L_JAMO',
      'JV' => 'HANGUL_V_JAMO',
      'JT' => 'HANGUL_T_JAMO',
      'RI' => 'REGIONAL_INDICATOR',
      'SA' => 'COMPLEX_CONTEXT_DEPENDENT',
      'XX' => 'UNKNOWN',
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
