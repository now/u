# -*- coding: utf-8 -*-

class U::Build::Data::Unicode::Entry::Decomposition
  include Enumerable

  def initialize(decomposition)
    @canonical = decomposition !~ /\A<.*>\s*(.*)/
    @points = U::Build::Data::Unicode::Points.new(@canonical ? decomposition : $1)
  end

  def canonical?
    @canonical
  end

  def empty?
    @points.empty?
  end

  def length
    @points.count
  end

  def each
    @points.each do |point|
      yield point
    end
    self
  end
end
