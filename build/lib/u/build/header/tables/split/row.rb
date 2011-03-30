# -*- coding: utf-8 -*-

class U::Build::Header::Tables::Split::Row
  include Enumerable

  def initialize(start)
    @start = start
    @cells = []
    # TODO: Perhaps don’t cache this if this turns out to be too memory
    # consuming.
    @homogenous = true
    0.upto(255) do |i|
      @cells[i] = yield(start + i)
      @homogenous = false if @cells[i] != @cells[0]
    end
  end

  def each
    @cells.each do |cell|
      yield cell
    end
    self
  end

  def [](index)
    @cells[index]
  end

  def homogenous?
    @homogenous
  end

  attr_reader :start
end
