# -*- coding: utf-8 -*-

class U::Build::Header::Table::Row
  def initialize(*cells)
    @cells = cells
  end

  def <<(cell)
    @cells << cell
    self
  end

  def to_s
    if @cells.reduce(0){ |i, cell| i + cell.length + 2 } > multi_limit
      lines = [Line.new]
      @cells.each_with_index do |cell, i|
        lines << Line.new if lines.last.length + cell.length + 2 > multi_limit - 3
        lines.last << cell
      end
      multi_format % lines.join(multi_joiner)
    else
      single_format % @cells.join(', ')
    end
  end

private

  def multi_limit
    65
  end

  def multi_format
    "\t{\n\t\t%s\n\t}"
  end

  def multi_joiner
    ",\n\t\t"
  end

  def single_format
    "\t{ %s }"
  end

  class Line
    def initialize
      @cells = []
      @length = 0
    end

    def <<(cell)
      @cells << cell
      @length += cell.length
      self
    end

    def length
      @length + (@cells.length - 1) * 2
    end

    def to_s
      @cells.join(', ')
    end
  end
end
