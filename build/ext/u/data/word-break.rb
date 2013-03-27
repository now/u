# -*- coding: utf-8 -*-

require 'u/build'

class Break
  def initialize(data, word_break, io = $stdout)
    U::Build::Header.new(io) do
      io.puts U::Build::Header::Tables::Split.new(data, 'uint8_t', 'word_break_property'){ |i|
        'UNICODE_WORD_BREAK_%s' % word_break[i].upcase
      }
    end
  end
end

Break.new(Marshal.load(File.open(ARGV[0], 'rb', &:read)), U::Build::Data::WordBreak.new(ARGV[1]))
