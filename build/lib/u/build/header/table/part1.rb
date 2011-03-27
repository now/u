# -*- coding: utf-8 -*-

class U::Build::Header::Table::Part1
  def initialize(declaration, first, last, rows, set = 0, io = $stdout)
    io.printf "\n\n%s = {\n", declaration
    # TODO: Check if we can use each or something, instead, or if we can use
    # an array for Rows.
    j = set
    first.step(last, 256) do |i|
      index = i / 256
      row = rows[index]
      io.print "\t"
      if row.homogenous?
        io.printf '%s + UNICODE_MAX_TABLE_INDEX', row[0]
      else
        io.printf '%d /* page %d */', j, row.start / 256
        j += 1
      end
      io.puts ','
    end
    io.puts "};"
    @set = j
  end

  attr_reader :set
end
