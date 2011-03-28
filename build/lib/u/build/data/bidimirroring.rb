# -*- coding: utf-8 -*-

class U::Build::Data::BidiMirroring
  include Enumerable

  def initialize(path)
    @entries = []
    File.open(path, 'rb') do |file|
      file.each_line.with_index do |line, index|
        next if line =~ /\A(?:#|\s*\Z)/
        fields = line.chomp.sub(/\s*#.*\Z/, '').split(/\s*;\s*/, -1)
        raise RuntimeError,
          '%s:%d: wrong number of fields: %d instead of 2' %
            [@path, index + 1, fields.size] unless
              fields.size == 2
        @entries << Entry.new(fields[0].hex, fields[1].hex)
      end
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
