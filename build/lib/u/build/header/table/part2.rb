# -*- coding: utf-8 -*-

class U::Build::Header::Table::Part2 < U::Build::Header::Table::Part1
  def initialize(declaration, last, rows, io = $stdout)
    super declaration, 0xe0000, last, rows, io
  end
end
