# -*- coding: utf-8 -*-

require 'u/build'

class CombiningClass
  def initialize(data, io = $stdout)
    U::Build::Header.new(io) do
      io.puts U::Build::Header::Tables::Split.new(data, 'uint8_t', 'combining_class'){ |i|
        '%d' % data[i].cclass
      }
    end
  end
end

CombiningClass.new(Marshal.load(File.open(ARGV[0], 'rb', &:read)))
