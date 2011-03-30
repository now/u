# -*- coding: utf-8 -*-

class U::Build::Header::Tables::Split
  require 'u/build/header/tables/split/row'
  require 'u/build/header/tables/split/rows'
  require 'u/build/header/tables/split/data'
  require 'u/build/header/tables/split/part1'
  require 'u/build/header/tables/split/part2'

  def initialize(first, middle, last, io, data, part1, part2 = nil)
    rows = Rows.new(0, last){ |c| yield(c) }
    Data.new data, rows, io
    p1 = Part1.new(part1, first, middle, rows, 0, io)
    Part2.new part2, last, rows, p1, io if part2
  end
end
