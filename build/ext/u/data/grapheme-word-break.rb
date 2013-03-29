# -*- coding: utf-8 -*-

require 'u/build'

class Break
  def initialize(data, breaks, name, io = $stdout)
    U::Build::Header.new(io) do
      io.puts U::Build::Header::Tables::Split.new(data, 'uint8_t', '%s_break_property' % name){ |i|
        'UNICODE_%s_BREAK_%s' % [name.upcase, breaks[i].upcase]
      }
    end
  end
end

Break.new Marshal.load(File.open(ARGV[0], 'rb', &:read)), U::Build::Data::Break.new(ARGV[1]), ARGV[2]
