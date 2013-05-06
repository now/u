# -*- coding: utf-8 -*-

class U::Build::Data::DerivedNormalizationProps
  def initialize(path)
    @entries = Hash.new{ |h, k| h[k] = Hash.new{ 'Y' } }
    U::Build::Data::File.each(path, 2..3) do |point, property, value|
      @entries[point][property] = value
    end
  end

  def [](point)
    @entries[point]
  end
end
