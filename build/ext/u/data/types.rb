# -*- coding: utf-8 -*-

require 'u/build'

class Types
  def initialize(data, name, version, io = $stdout)
    U::Build::Header.new(name, io) do
      io.puts <<EOH
#define UNICODE_DATA_VERSION "#{version}"

#define UNICODE_LAST_CHAR #{sprintf('0x%04x', data.last)}

#define UNICODE_MAX_TABLE_INDEX 10000

#define UNICODE_LAST_CHAR_PART1 #{data.last_char_part1_x}

#define UNICODE_LAST_PAGE_PART1 #{data.pages_before_e0000 - 1}

#define UNICODE_FIRST_CHAR_PART2 0xe0000
EOH
      io.puts U::Build::Header::Tables::Split.
        new(0, data.last_char_part1_i, data.last,
            'static const char type_data[][256]',
            "/* U+0000 through U+%s */\nstatic const int16_t type_table_part1[%s]" % [data.last_char_part1_X, data.pages_before_e0000],
            "/* U+E0000 through U+%04X */\nstatic const int16_t type_table_part2[768]" % data.last){ |i|
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
      'Mc' => 'UNICODE_COMBINING_MARK',
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

Types.new(U::Build::Data::Unicode.new(ARGV[0]), ARGV[1], ARGV[2])
