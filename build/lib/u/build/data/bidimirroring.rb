# -*- coding: utf-8 -*-

class U::Build::Data::BidiMirroring
  include Enumerable

  def initialize(path)
    @entries = []
    U::Build::Data::File.each(path, 2) do |point, mirrored|
      @entries << Entry.new(point, mirrored.hex)
    end
  end

  def each
    @entries.each do |entry|
      yield entry
    end
  end

  class Entry
    def initialize(char, mirrored)
      @char, @mirrored = char, mirrored
    end

    attr_reader :char, :mirrored
  end
end
