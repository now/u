# -*- coding: utf-8 -*-

class U::Build::Data::LineBreak
  def initialize(data, path)
    @entries = []
    U::Build::Data::File.each_with_unlisted(path, 2) do |point, previous, unlisted, property|
      @entries[point] = unlisted ? (data[point].type == 'Cn' ? 'XX' : 'AL') : property
    end
  end

  def [](point)
    @entries[point]
  end
end
