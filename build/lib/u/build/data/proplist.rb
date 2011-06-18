# -*- coding: utf-8 -*-

class U::Build::Data::PropList
  include Enumerable

  def initialize(path)
    @entries = Hash.new{ |h, k| h[k] = [] }
    U::Build::Data::File.each(path, 2) do |point, property|
      @entries[point] << property
    end
  end

  def each
    @entries.each do |point, properties|
      yield point, properties
    end
  end
end
