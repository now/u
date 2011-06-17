# -*- coding: utf-8 -*-

class U::Build::Header::Tables::Split::Part1 < U::Build::Header::Table
  class << self
    def last_page
      'UNICODE_LAST_PAGE_PART1'
    end
  end

  def initialize(name, first, last, rows, set = 0)
    super "/* U+%04X through U+%04X */\nstatic const int16_t %s[%s + 1]" % [first, last, name, self.class.last_page]
    # TODO: Check if we can use each or something, instead, or if we can use
    # an array for Rows.
    j = set
    first.step(last, 256) do |i|
      row = rows[i / 256]
      if row.homogenous?
        self << "\t%s + UNICODE_MAX_TABLE_INDEX" % row[0]
      else
        self << "\t%d /* page %d */" % [j, row.start / 256]
        j += 1
      end
    end
    @set = j
  end

  attr_reader :set
end
