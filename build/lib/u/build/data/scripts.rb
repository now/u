# -*- coding: utf-8 -*-

class U::Build::Data::Scripts
  include Enumerable

  def initialize(path)
    @entries = {}
    U::Build::Data::File.each(path, 2) do |point, script|
      @entries[point] = script
    end
  end

  def [](point)
    @entries.fetch(point, 'Unknown')
  end

  def each
    @entries.each do |point, script|
      yield point, script
    end
  end
end
