# -*- coding: utf-8 -*-

class U::Build::Header::Tables::Split::Part2 < U::Build::Header::Tables::Split::Part1
  def initialize(declaration, last, rows, part1)
    super declaration, 0xe0000, last, rows, part1.set
  end
end
