# -*- coding: utf-8 -*-

require 'u/build'

class Cased
  Cased = ['Other_Lowercase', 'Other_Uppercase'].freeze

  def initialize(prop_list, io = $stdout)
    U::Build::Header.new(io) do
      io.puts U::Build::Header::Tables::Intervals.
        new(prop_list.
              select{ |point, properties| properties.any?{ |property| Cased.include? property } }.
              map{ |point, properties| point },
            'cased')
    end
  end
end

Cased.new(U::Build::Data::PropList.new(ARGV[0]))
