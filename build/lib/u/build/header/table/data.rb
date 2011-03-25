# -*- coding: utf-8 -*-

class U::Build::Header::Table::Data
  def initialize(declaration, rows, io = $stdout)
    io.printf "\n\n%s = {\n", declaration
    rows.reject{ |row| row.homogenous? }.each_with_index do |row, index|
      io.puts ',' unless index.zero?
      io.printf "\t{ /* page %d, index %d */\n\t\t", row.start / 256, index
      column = 16
      row.each do |cell|
        if column + cell.length + 2 > 79
          io.print "\n\t\t"
          column = 16
        end
        io.printf '%s, ', cell
        column += cell.length + 2
      end
      print "\n\t}"
    end
    puts "\n};"
  end
end
