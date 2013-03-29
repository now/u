# -*- coding: utf-8 -*-

class U::Build::Data::Break
  def initialize(path)
    @entries = Hash.new{ 'Other' }
    U::Build::Data::File.each(path, 2) do |point, property|
      @entries[point] = property
    end
  end

  def [](point)
    @entries[point]
  end
end
