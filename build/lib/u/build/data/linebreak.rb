# -*- coding: utf-8 -*-

class U::Build::Data::LineBreak
  def initialize(data, path)
    @entries = []
    Lines.new(data, path).each do |code, property|
      @entries[code] = property
    end
  end

  def [](code)
    @entries[code]
  end

private

  class Lines
    def initialize(data, path)
      @data, @path = data, path
    end

    def each
      File.open(@path, 'rb') do |file|
        previous = -1
        file.each_line.with_index do |line, index|
          next if line =~ /\A(?:#|\s*\Z)/
          fields = line.chomp.sub(/\s*#.*\Z/, '').split(/\s*;\s*/)
          raise RuntimeError,
            '%s:%d: wrong number of fields: %d instead of 2' %
              [@path, index + 1, fields.size] unless fields.size == 2
          if fields[Code] =~ /\A([0-9A-F]{4,6})\.\.([0-9A-F]{4,6})\Z/
            first, last = $1.hex, $2.hex
          else
            first = last = fields[Code].hex
          end
          gap previous + 1, first - 1, &Proc.new if first > previous + 1
          first.upto(last) do |i|
            yield i, fields[Property]
          end
          previous = last
        end
        gap previous + 1, 0x10ffff, &Proc.new
      end
    end

  private

    def gap(first, last)
      first.upto(last) do |i|
        yield i, @data[i].type == 'Cn' ? 'XX' : 'AL'
      end
    end

    Code, Property = (0..1).to_a
  end
end
