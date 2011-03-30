# -*- coding: utf-8 -*-

class U::Build::Data::SpecialCasing
  include Enumerable

  def initialize(data, path)
    @entries = {}
    File.new(data, path).each do |point, entry|
      @entries[point] = entry
    end
  end

  def include?(point)
    @entries.include? point
  end

  def [](point)
    @entries[point]
  end

  def each
    @entries.values.sort.each do |entry|
      yield entry
    end
  end

  # TODO: Move to its own file
  class Entry
    include Comparable

    def initialize(points, offset)
      @points, @offset = points, offset
    end

    def <=>(other)
      self.class == other.class ?
        offset <=> other.offset :
        nil
    end

    def to_s
      @points.to_s
    end

    def to_escaped_s
      @points.to_escaped_s
    end

    attr_reader :offset
  end

private

  class File
    def initialize(data, path)
      @data, @path = data, path
      @offset = 0
    end

    def each
      U::Build::Data::File.each(@path, 5..6) do |point, lower, title, upper, condition, _comment|
        raise RuntimeError,
          'special case for code point that does not have a type: %04X' %
            point unless
              @data[point].type
        # We deal with conditional special cases in code.
        next unless condition.empty?
        yield point, case @data[point].type
        when 'Lu'
          verify upper, point, 'Lu', 'Upper'
          entry(@data[point].value, lower, title)
        when 'Lt'
          verify title, point, 'Lt', 'Title'
          entry(nil, lower, upper)
        when 'Ll'
          verify lower, point, 'Ll', 'Lower'
          entry(@data[point].value, upper, title)
        else
          raise RuntimeError,
            'special case entry of type %s for non-alphabetic code point: %04X' %
              [@data[point].type, point]
        end
      end
    end

  private

    def verify(field, point, type, ccase)
      raise RuntimeError,
        'special case entry has type %s, but UCD_%s(%04X) != %04X: %04X' %
          [type, ccase, point, point, point] unless
            field.hex == point
    end

    def entry(single, field1, field2)
      Entry.new(U::Build::Data::Unicode::Points.new([
        single ? single.to_s(16) : nil,
        field1,
        "\0",
        field2
      ].compact.join(' ')), @offset).tap{ |e|
        @offset += e.to_s.length + 1
      }
    end
  end
end
