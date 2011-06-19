# -*- coding: utf-8 -*-

require 'u/build'

class SoftDotted
  def initialize(prop_list, io = $stdout)
    U::Build::Header.new(io) do
      io.puts U::Build::Header::Tables::Intervals.
        new(prop_list.
              select{ |point, properties| properties.include? 'Soft_Dotted' }.
              map{ |point, properties| point },
            'soft_dotted')
    end
  end
end

SoftDotted.new(U::Build::Data::PropList.new(ARGV[0]))
