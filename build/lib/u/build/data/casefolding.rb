# -*- coding: utf-8 -*-

class U::Build::Data::CaseFolding
  include Enumerable

  def initialize(data, special_casing, path)
    @entries = []
    File.new(data, special_casing, path).each do |entry|
      @entries << entry
    end
  end

  def each
    @entries.each do |entry|
      yield entry
    end
  end

  class Entry
    def initialize(char, points)
      @char, @points = char, points
    end

    def to_s
      @points.to_s
    end

    def to_escaped_s
      @points.to_escaped_s
    end

    attr_reader :char
  end

private

  class File
    def initialize(data, special_casing, path)
      @data, @special_casing, @path = data, special_casing, path
    end

    def each
      U::Build::Data::File.each(@path, 4) do |point, status, mapping|
        next if simple_or_turkic? status
        points = U::Build::Data::Unicode::Points.new(mapping)
        next if simple? points, point
        yield Entry.new(point, points)
      end
    end

  private

    def simple_or_turkic?(status)
      %w[S T].include? status
    end

    def simple?(points, code)
      points.length == 1 and
        not @special_casing.include? code and
        @data[code].type and
        lower(code) == points.first
    end

    def lower(code)
      case @data[code].type
      when 'Ll'
        code
      when 'Lt'
        @data[code].title_to_lower
      when 'Lu'
        @data[code].value
      else
        code
      end
    end
  end
end
