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
      'Cc' => 'OTHER_CONTROL',
      'Cf' => 'OTHER_FORMAT',
      'Cn' => 'OTHER_NOT_ASSIGNED',
      'Co' => 'OTHER_PRIVATE_USE',
      'Cs' => 'OTHER_SURROGATE',
      'Ll' => 'LETTER_LOWERCASE',
      'Lm' => 'LETTER_MODIFIER',
      'Lo' => 'LETTER_OTHER',
      'Lt' => 'LETTER_TITLECASE',
      'Lu' => 'LETTER_UPPERCASE',
      'Mc' => 'MARK_SPACING_COMBINING',
      'Me' => 'MARK_ENCLOSING',
      'Mn' => 'MARK_NON_SPACING',
      'Nd' => 'NUMBER_DECIMAL',
      'Nl' => 'NUMBER_LETTER',
      'No' => 'NUMBER_OTHER',
      'Pc' => 'PUNCTUATION_CONNECTOR',
      'Pd' => 'PUNCTUATION_DASH',
      'Pe' => 'PUNCTUATION_CLOSE',
      'Pf' => 'PUNCTUATION_FINAL_QUOTE',
      'Pi' => 'PUNCTUATION_INITIAL_QUOTE',
      'Po' => 'PUNCTUATION_OTHER',
      'Ps' => 'PUNCTUATION_OPEN',
      'Sc' => 'SYMBOL_CURRENCY',
      'Sk' => 'SYMBOL_MODIFIER',
      'Sm' => 'SYMBOL_MATH',
      'So' => 'SYMBOL_OTHER',
      'Zl' => 'SEPARATOR_LINE',
      'Zp' => 'SEPARATOR_PARAGRAPH',
      'Zs' => 'SEPARATOR_SPACE',
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
