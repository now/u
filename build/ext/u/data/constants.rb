# -*- coding: utf-8 -*-

require 'u/build'

class Constants
  def initialize(data, version, io = $stdout)
    # TODO: Defines should be made with a list, but we can’t match formatting
    # quite yet, so wait until we have stable tests.
    U::Build::Header.new(io) do
      io.puts <<EOH
#define UNICODE_DATA_VERSION "#{version}"

#define UNICODE_LAST_CHAR #{'%#04x' % data.last}

#define UNICODE_MAX_TABLE_INDEX ((UNICODE_LAST_CHAR + 1) / 256)

#define UNICODE_LAST_CHAR_PART1 #{data.last_char_part1_x}

#define UNICODE_FIRST_CHAR_PART2 0xe0000

#define UNICODE_LAST_PAGE_PART1 (UNICODE_LAST_CHAR_PART1 / 256)

#define UNICODE_LAST_PAGE_PART2 ((UNICODE_LAST_CHAR + 1 - UNICODE_FIRST_CHAR_PART2) / 256)

#define UNICODE_SPECIAL_CASE_TABLE_START 0x1000000
EOH
    end
  end
end

Constants.new(U::Build::Data::Unicode.new(ARGV[0]), ARGV[1])
