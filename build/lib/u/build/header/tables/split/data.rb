# -*- coding: utf-8 -*-

class U::Build::Header::Tables::Split::Data < U::Build::Header::Table
  def initialize(declaration, rows)
    super declaration
    rows.reject{ |row| row.homogenous? }.each_with_index do |row, index|
      table_row = Row.new(row.start / 256, index)
      row.each do |cell|
        table_row << cell
      end
      self << table_row
    end
  end

private

  class Row < U::Build::Header::Table::Row
    def initialize(page, index)
      super()
      @format = "\t{ /* page %d, index %d */\n\t\t%%s\n\t}" % [page, index]
    end

  private

    def multi_format
      @format
    end
  end
end
