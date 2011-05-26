# -*- coding: utf-8 -*-

class U::Build::Data::DerivedEastAsianWidth
  include Enumerable

  def initialize(path)
    @path = path
  end

  def each
    U::Build::Data::File.each(@path, 2) do |point, width|
      yield point, width
    end
  end
end
