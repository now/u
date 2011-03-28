# -*- coding: utf-8 -*-

class U::Build::Data::SpecialCasing
  include Enumerable

  def initialize(data, path)
    @entries = []

    # TODO: Why not include Enumerable and #to_a Lines instead?
    Lines.new(data, path).each do |entry|
      @entries << entry
    end
  end

  def each
    @entries.each do |entry|
      yield entry
    end
  end

  # TODO: Move to its own file
  class Entry
    def initialize(value, offset)
      @value, @offset = value, offset
    end

    def to_s
      @value
    end

    attr_reader :offset
  end

private

  class Lines
    def initialize(data, path)
      @data, @path = data, path
      @offset = 0
    end

    def each
      File.open(@path, 'rb') do |file|
        file.each_line.with_index do |line, index|
          next if line =~ /\A(?:#|\s*\Z)/
          fields = line.chomp.sub(/\s*#.*\Z/, '').split(/\s*;\s*/, -1)
          raise RuntimeError,
            '%s:%d: wrong number of fields: %d instead of 5..6' %
              [@path, index + 1, fields.size] unless
                fields.size.between? 5, 6
          raw_code, code = fields[Code], fields[Code].hex
          raise RuntimeError,
            '%s:%d: special case for code point that does not have a type: %d' %
              [@path, index + 1, code] unless
                @data[code].type
          # We deal with conditional special cases in code.
          next if fields.size == 6
          yield case @data[code].type
          when 'Lu'
            verify index, fields[Upper], code, raw_code, 'Lu', 'Upper'
            entry(code, @data[code].value, fields[Lower], fields[Title])
          when 'Lt'
            verify index, fields[Title], code, raw_code, 'Lt', 'Title'
            entry(code, nil, fields[Lower], fields[Upper])
          when 'Ll'
            verify index, fields[Lower], code, raw_code, 'Ll', 'Lower'
            entry(code, @data[code].value, fields[Upper], fields[Title])
          else
            raise RuntimeError,
              '%s:%d: special case entry of type %s for non-alphabetic code point: %s' %
                [@path, index + 1, @data[code].type, raw_code]
          end
        end
      end
    end

  private

    def verify(index, field, code, raw_code, type, ccase)
      raise RuntimeError,
        '%s:%d: special case entry has type %s, but UCD_%s(%s) != %s: %s' %
          [@path, index + 1, type, ccase, raw_code, raw_code, raw_code] unless
            field.hex == code
    end

    def entry(code, single, field1, field2)
      value = [ single ? [single] : nil,
                  field1.split(/\s+/).map{ |s| s.hex },
                  [0],
                  field2.split(/\s+/).map{ |s| s.hex }
                ].compact.
                  map{ |v| v.pack('U*') }.
                  join('')
      # TODO: Move this escaping to Entry
      Entry.new(value.unpack('H*')[0].gsub(/(.{2})/, '\\x\1'), @offset).tap{ |e|
        @data[code].value = 0x1000000 + @offset
        @offset += value.length + 1
      }
    end

    Code, Lower, Title, Upper, Condition, Comment = (0..5).to_a
  end
end
