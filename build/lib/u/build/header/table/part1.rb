# -*- coding: utf-8 -*-

class U::Build::Header::Table::Part1
  def initialize(declaration, first, last, rows, io = $stdout)
    io.printf "\n\n%s = {\n", declaration
    # TODO: Check if we can use each or something, instead, or if we can use
    # an array for Rows.
    j = 0
    first.step(last, 256) do |i|
      index = i / 256
      row = rows[index]
      print "\t"
      if row.homogenous?
        printf '%s + UNICODE_MAX_TABLE_INDEX', row[0]
      else
        printf '%d /* page %d */', j, row.start / 256
        j += 1
      end
      puts ','
    end
    puts "};"
  end
end
