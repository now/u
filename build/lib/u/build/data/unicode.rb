# -*- coding: utf-8 -*-

class U::Build::Data::Unicode
  include Enumerable

  require 'u/build/data/unicode/points'
  require 'u/build/data/unicode/entry'

  Name, Category, CombiningClasses, _, Decomposition, DecimalValue, _, _, _, _, _, Upper, Lower, _ = (0..13).to_a

  def initialize(path)
    @entries = []
    U::Build::Data::File.each_with_unlisted(path, 15) do |point, previous, unlisted, *fields|
      if point >= 0xe0000 and previous < 0xe0000
        @pages_before_e0000 = (previous >> 8) + 1
        @last_char_part1_i = @pages_before_e0000 * 256 - 1
        @last_char_part1_x = '0x%04x' % @last_char_part1_i
        @last_char_part1_X = '%04X' % @last_char_part1_i
      end
      @entries << Entry.new(point,
                            (unlisted and fields[Name] !~ /Last>\Z/) ? Unlisted : fields)
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

  Unlisted = ['', 'Cn', '0', '', '', '', '', '', '', '', '', '', '', ''].freeze
end
