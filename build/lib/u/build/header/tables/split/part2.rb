# -*- coding: utf-8 -*-

class U::Build::Header::Tables::Split::Part2 < U::Build::Header::Tables::Split::Part1
  class << self
    def last_page
      'UNICODE_LAST_PAGE_PART2'
    end
  end

  def initialize(name, last, rows, part1)
    super name, 0xe0000, last, rows, part1.set
  end
end
