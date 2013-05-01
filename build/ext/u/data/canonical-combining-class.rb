# -*- coding: utf-8 -*-

require 'u/build'

class CanonicalCombiningClass
  def initialize(data, io = $stdout)
    U::Build::Header.new(io) do
      io.puts U::Build::Header::Tables::Split.new(data, 'uint8_t', 'canonical_combining_class'){ |i|
        '%d' % data[i].cclass
      }
    end
  end
end

CanonicalCombiningClass.new(Marshal.load(File.open(ARGV[0], 'rb', &:read)))
