# -*- coding: utf-8 -*-

class U::Build::Header::Table::Part2 < U::Build::Header::Table::Part1
  def initialize(declaration, last, rows, part1, io = $stdout)
    super declaration, 0xe0000, last, rows, part1.set, io
  end
end
