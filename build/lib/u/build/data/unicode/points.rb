# -*- coding: utf-8 -*-

class U::Build::Data::Unicode::Points
  include Enumerable

  def initialize(string)
    @points = string.split(/\s+/).map{ |s| s.hex }
  end

  def empty?
    @points.empty?
  end

  def length
    @points.length
  end

  def each
    @points.each do |point|
      yield point
    end
    self
  end
end
