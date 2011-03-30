# -*- coding: utf-8 -*-

class U::Build::Data::CompositionExclusions
  def initialize(path)
    @entries = {}
    U::Build::Data::File.each(path, 1) do |point|
      @entries[point] = true
    end
  end

  def include?(code)
    @entries.include? code
  end
end
