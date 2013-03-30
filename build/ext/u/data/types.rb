# -*- coding: utf-8 -*-

require 'u/build'

class Types
  def initialize(data, io = $stdout)
    U::Build::Header.new(io) do
      io.puts U::Build::Header::Tables::Split.new(data, 'char', 'type'){ |i|
        'U_%s' % Mappings[data[i].type]
      }
    end
  end

private

  # Map general category code onto symbolic name.
  module Mappings
    Mappings = {
      # Normative.
      'Lu' => 'UPPERCASE_LETTER',
      'Ll' => 'LOWERCASE_LETTER',
      'Lt' => 'TITLECASE_LETTER',
      'Mn' => 'NON_SPACING_MARK',
      'Mc' => 'SPACING_MARK',
      'Me' => 'ENCLOSING_MARK',
      'Nd' => 'DECIMAL_NUMBER',
      'Nl' => 'LETTER_NUMBER',
      'No' => 'OTHER_NUMBER',
      'Zs' => 'SPACE_SEPARATOR',
      'Zl' => 'LINE_SEPARATOR',
      'Zp' => 'PARAGRAPH_SEPARATOR',
      'Cc' => 'CONTROL',
      'Cf' => 'FORMAT',
      'Cs' => 'SURROGATE',
      'Co' => 'PRIVATE_USE',
      'Cn' => 'UNASSIGNED',

      # Informative.
      'Lm' => 'MODIFIER_LETTER',
      'Lo' => 'OTHER_LETTER',
      'Pc' => 'CONNECT_PUNCTUATION',
      'Pd' => 'DASH_PUNCTUATION',
      'Ps' => 'OPEN_PUNCTUATION',
      'Pe' => 'CLOSE_PUNCTUATION',
      'Pi' => 'INITIAL_PUNCTUATION',
      'Pf' => 'FINAL_PUNCTUATION',
      'Po' => 'OTHER_PUNCTUATION',
      'Sm' => 'MATH_SYMBOL',
      'Sc' => 'CURRENCY_SYMBOL',
      'Sk' => 'MODIFIER_SYMBOL',
      'So' => 'OTHER_SYMBOL'
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

Types.new(Marshal.load(File.open(ARGV[0], 'rb', &:read)))
