# -*- coding: utf-8 -*-

require 'u/build'

class Wide
  def initialize(derived_east_asian_width, types, io = $stdout)
    U::Build::Header.new(io) do
      io.puts U::Build::Header::Tables::Intervals.
        new(derived_east_asian_width.
              select{ |point, width| types.include? width }.
              map{ |point, width| point },
            'wide')
    end
  end
end

Wide.new(U::Build::Data::DerivedEastAsianWidth.new(ARGV[0]), ARGV[1..-1])
