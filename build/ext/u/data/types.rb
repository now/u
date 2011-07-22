# -*- coding: utf-8 -*-

require 'u/build'

class Types
  def initialize(data, io = $stdout)
    U::Build::Header.new(io) do
      io.puts U::Build::Header::Tables::Split.new(data, 'char', 'type'){ |i|
        Mappings[data[i].type]
      }
    end
  end

private

  # Map general category code onto symbolic name.
  module Mappings
    Mappings = {
      # Normative.
      'Lu' => 'UNICODE_UPPERCASE_LETTER',
      'Ll' => 'UNICODE_LOWERCASE_LETTER',
      'Lt' => 'UNICODE_TITLECASE_LETTER',
      'Mn' => 'UNICODE_NON_SPACING_MARK',
      'Mc' => 'UNICODE_SPACING_MARK',
      'Me' => 'UNICODE_ENCLOSING_MARK',
      'Nd' => 'UNICODE_DECIMAL_NUMBER',
      'Nl' => 'UNICODE_LETTER_NUMBER',
      'No' => 'UNICODE_OTHER_NUMBER',
      'Zs' => 'UNICODE_SPACE_SEPARATOR',
      'Zl' => 'UNICODE_LINE_SEPARATOR',
      'Zp' => 'UNICODE_PARAGRAPH_SEPARATOR',
      'Cc' => 'UNICODE_CONTROL',
      'Cf' => 'UNICODE_FORMAT',
      'Cs' => 'UNICODE_SURROGATE',
      'Co' => 'UNICODE_PRIVATE_USE',
      'Cn' => 'UNICODE_UNASSIGNED',

      # Informative.
      'Lm' => 'UNICODE_MODIFIER_LETTER',
      'Lo' => 'UNICODE_OTHER_LETTER',
      'Pc' => 'UNICODE_CONNECT_PUNCTUATION',
      'Pd' => 'UNICODE_DASH_PUNCTUATION',
      'Ps' => 'UNICODE_OPEN_PUNCTUATION',
      'Pe' => 'UNICODE_CLOSE_PUNCTUATION',
      'Pi' => 'UNICODE_INITIAL_PUNCTUATION',
      'Pf' => 'UNICODE_FINAL_PUNCTUATION',
      'Po' => 'UNICODE_OTHER_PUNCTUATION',
      'Sm' => 'UNICODE_MATH_SYMBOL',
      'Sc' => 'UNICODE_CURRENCY_SYMBOL',
      'Sk' => 'UNICODE_MODIFIER_SYMBOL',
      'So' => 'UNICODE_OTHER_SYMBOL'
    }.freeze

    class << self
      def [](value)
        Mappings[value] or
          raise 'unknown Category property value: %s; the Unicode standard has changed' %
            value
      end
    end
  end
end

Types.new(U::Build::Data::Unicode.new(ARGV[0]))
