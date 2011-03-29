# -*- coding: utf-8 -*-

class U::Build::Data::Unicode
  include Enumerable

  require 'u/build/data/unicode/points'
  require 'u/build/data/unicode/entry'

  Code, Name, Category, CombiningClasses, _, Decomposition, DecimalValue, _, _, _, _, _, Upper, Lower, _ = (0..14).to_a

  def initialize(path)
    @entries = []

    Lines.new(path).each do |code, value|
      case value
      when Array
        @entries << Entry.new(code, value)
      else
        # TODO: Make sure only called once
        @pages_before_e0000 = value
        @last_char_part1_i = @pages_before_e0000 * 256 - 1
        @last_char_part1_x = '0x%04x' % @last_char_part1_i
        @last_char_part1_X = '%04X' % @last_char_part1_i
      end
    end
    @last = 0x10ffff
  end

  attr_reader :pages_before_e0000, :last_char_part1_i, :last_char_part1_x, :last_char_part1_X, :last

  def [](index)
    @entries[index]
  end

  def each
    @entries.each do |entry|
      yield entry
    end
  end

private

  class Lines
    include Enumerable

    def initialize(path)
      @path = path
    end

    def each
      File.open(@path, 'rb') do |file|
        previous = -1
        file.enum_for(:each_line).with_index do |line, index|
          next if line =~ /\A(?:#|\s*\Z)/
          fields = line.chomp.sub(/\s*;\s*#.*\Z/, '').split(/\s*;\s*/, -1)
          raise RuntimeError,
            '%s:%d: wrong number of fields: %d instead of 15' %
              [@path, index + 1, fields.size] unless fields.size == 15
          code = fields[Code].hex
          yield nil, (previous >> 8) + 1 if code >= 0xe0000 and previous < 0xe0000
          gap previous + 1,
            code - 1,
            fields[Name] =~ /Last>\Z/ ? fields : GapFields,
            &Proc.new if code > previous + 1
          yield code, fields
          previous = code
        end
        gap previous + 1, 0x10ffff, GapFields, &Proc.new
      end
    end

  private

    GapFields = ['', '', 'Cn', '0', '', '', '', '', '', '', '', '', '', '', ''].freeze

    def gap(first, last, fields)
      first.upto(last) do |i|
        yield i, fields
      end
    end
  end
end
