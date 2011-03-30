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
    if @cells.reduce(0){ |i, cell| i + cell.length + 2 } > 65
      lines = [Line.new]
      @cells.each_with_index do |cell, i|
        # TODO: Change this to 62.  This is set to 61 to match the current
        # format.
        lines << Line.new if lines.last.length + cell.length + 2 > 61
        lines.last << cell
      end
      multi_format % lines.join(",\n\t\t")
    else
      "\t{ %s }" % @cells.join(', ')
    end
  end

private

  def multi_format
    "\t{\n\t\t%s\n\t}"
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
