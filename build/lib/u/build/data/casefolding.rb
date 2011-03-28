# -*- coding: utf-8 -*-

class U::Build::Data::CaseFolding
  include Enumerable

  def initialize(data, path)
    @entries = []
    Lines.new(data, path).each do |entry|
      @entries << entry
    end
  end

  def each
    @entries.each do |entry|
      yield entry
    end
  end

  class Entry
    def initialize(char, string)
      @char, @string = char, string
    end

    def to_s
      @string
    end

    def escaped
      @string.unpack('H*')[0].gsub(/(.{2})/, '\\x\1')
    end

    attr_reader :char
  end

private

  class Lines
    def initialize(data, path)
      @data, @path = data, path
    end

    def each
      File.open(@path, 'rb') do |file|
        file.each_line.with_index do |line, index|
          next if line =~ /\A(?:#|\s*\Z)/
          fields = line.chomp.sub(/\s*#.*\Z/, '').split(/\s*;\s*/, -1)
          raise RuntimeError,
            '%s:%d: wrong number of fields: %d instead of 4' %
              [@path, index + 1, fields.size] unless
                fields.size == 4
          # Simple and Turkic rules are dealt with in code.
          next if ['S', 'T'].include? fields[Status]
          code = fields[Code].hex
          # TODO: This splitting and mapping is duplicated.
          values = fields[Mapping].split(/\s+/).map{ |s| s.hex }
          next if simple? values, code
          yield Entry.new(code, values.pack('U*'))
        end
      end
    end

  private

    def simple?(values, code)
      values.size == 1 and
        not (@data[code].value and @data[code].value >= 0x1000000) and
        @data[code].type and
        lower(code) == values[0]
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

  Code, Status, Mapping = (0..2).to_a
end
