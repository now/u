# -*- coding: utf-8 -*-

module Utfify
  class << self
    def utfify(codepoints)
      return '' if codepoints.empty?
      codepoints.split(/\s+/).map{ |cp| cp.hex }.pack('U*')
    end
  end
end

class SpecialCasing
  def initialize(path)
    @entries = []

    Lines.new(path).each do |fields|
      @entries[fields[Code].hex] =
        Entry.new(Utfify.utfify(fields[Upper]),
                  Utfify.utfify(fields[Lower]),
                  Utfify.utfify(fields[Title]),
                  fields[Condition])
    end
  end

  def include?(code)
    @entries[code]
  end

  def [](code)
    @entries[code]
  end

  class Entry
    def initialize(upper, lower, title, condition)
      @upper, @lower, @title, @condition = upper, lower, title, condition
    end

    attr_reader :upper, :lower, :title, :condition
  end

private

  Code, Lower, Title, Upper, Condition = (0..4).to_a

  class Lines
    include Enumerable

    def initialize(path)
      @path = path
    end

    def each
      File.open(@path, 'rb') do |file|
        file.enum_for(:each_line).with_index do |line, index|
          next if line =~ /\A(?:#|\s*\Z)/
          fields = line.chomp.sub(/\s*;\s*#.*\Z/, '').split(/\s*;\s*/)
          raise RuntimeError,
            '%s:%d: wrong number of fields: %d instead of 4..5' %
              [@path, index + 1, fields.size] unless fields.size.between? 4, 5
          yield fields
        end
      end
    end
  end
end

class UnicodeData
  include Enumerable

  def initialize(path)
    @entries = []

    Lines.new(path).each do |code, fields|
      @entries << Entry.new(code, fields[Category], fields[Upper], fields[Lower])
    end
  end

  def each
    @entries.each do |entry|
      yield entry
    end
  end

  class Entry
    def initialize(code, category, upper, lower)
      @code, @category, @upper, @lower = code, category, upper, lower
    end

    attr_reader :code, :category, :upper, :lower
  end

private

  Code, Name, Category, _, _, _, _, _, _, _, _, _, Upper, Lower, Title = (0..14).to_a

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
          fields = line.split(';')
          raise RuntimeError,
            '%s:%d: wrong number of fields: %d instead of 15' %
              [@path, index + 1, fields.size] unless fields.size == 15
          code = fields[Code].hex
          if code > previous + 1 and fields[Name] =~ /Last>$/ and fields[Category] =~ /^L[lut]$/
            previous.upto(code - 1) do |c|
              yield c, fields
            end
          end
          yield code, fields
          previous = code
        end
      end
    end
  end
end

class Case
  def initialize(special, unicode_data, io = $stdout)
    @special, @io = special, io
    @io.puts '# -*- coding: utf-8 -*-',
      '# Automatically generated, so don’t edit!',
      '',
      'Expectations do'
    unicode_data.each do |entry|
      generate entry
    end
    @io.puts 'end'
  end

private

  def generate(entry)
    case entry.category
    when 'Ll'
      upcase entry
    when 'Lu'
      downcase entry
    when 'Lt'
      upcase entry
      downcase entry
    end
  end

  def upcase(entry)
    if @special.include? entry.code
      generate1 @special[entry.code].upper, u(entry), :upcase if not @special[entry.code].condition
    elsif not entry.upper.empty?
      generate1 Utfify.utfify(entry.upper), u(entry), :upcase
    end
  end

  def downcase(entry)
    if @special.include? entry.code
      generate1 @special[entry.code].lower, u(entry), :downcase if not @special[entry.code].condition
    elsif not entry.lower.empty?
      generate1 Utfify.utfify(entry.lower), u(entry), :downcase
    end
  end

  def generate1(expected, u, method)
    @io.printf "  expect '%s'.u do %s.%s end\n", expected, u, method
  end

  def u(entry)
    "'%s'.u" % [entry.code].pack('U*')
  end
end

Case.new SpecialCasing.new(ARGV[0]), UnicodeData.new(ARGV[1])
