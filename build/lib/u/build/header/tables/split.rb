# -*- coding: utf-8 -*-

class U::Build::Header::Tables::Split
  require 'u/build/header/tables/split/row'
  require 'u/build/header/tables/split/rows'
  require 'u/build/header/tables/split/data'
  require 'u/build/header/tables/split/part1'
  require 'u/build/header/tables/split/part2'

  def initialize(data, type, name)
    rows = Rows.new(0, data.last){ |c| yield(c) }
    @data = Data.new('%s %s_data' % [type, name], rows)
    @part1 = Part1.new('%s_table_part1' % name, 0, data.last_char_part1_i, rows, 0)
    @part2 = Part2.new('%s_table_part2' % name, data.last, rows, @part1)
  end

  def to_s
    "%s\n%s\n%s" % [@data, @part1, @part2]
  end
end
