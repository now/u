# -*- coding: utf-8 -*-

class U::Build::Header::Table::Rows
  include Enumerable

  def initialize(first, last)
    @rows = []
    first.step(last, 256) do |i|
      @rows[i / 256] = U::Build::Header::Table::Row.new(i){ |c| yield(c) }
    end
  end

  def each
    @rows.each do |row|
      yield row
    end
  end

  def [](index)
    @rows[index]
  end
end
