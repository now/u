# -*- coding: utf-8 -*-

class U::Build::Data::File
  class << self
    def open(path, fields)
      file = new(path, fields)
      begin
        yield file
      ensure
        file.close
      end
    end

    def each(path, fields)
      open(path, fields) do |file|
        file.each do |point, *fs|
          yield point, *fs
        end
      end
    end

    def each_with_unlisted(path, fields)
      open(path, fields) do |file|
        file.each_with_unlisted do |point, previous, unlisted, *fs|
          yield point, previous, unlisted, *fs
        end
      end
    end
  end

  def initialize(path, fields)
    @path, @fields = path, fields
    @file = File.open(@path, 'rb')
  end

  def close
    @file.close
    self
  end

  def each
    @file.each_line.with_index do |line, index|
      next if comment_or_empty? line
      fields = line.sub(/\s*#.*\Z/, '').strip.split(/\s*;\s*/, -1)
      raise RuntimeError,
        '%s:%d: wrong number of fields: %d instead of %d' %
          [@path, index + 1, fields.size, @fields] unless
            @fields === fields.size
      code = fields.shift
      if code =~ /\A([0-9A-Fa-f]{4,6})\.\.([0-9A-Fa-f]{4,6})\Z/
        first, last = $1.hex, $2.hex
      else
        first = last = code.hex
      end
      begin
        first.upto(last) do |point|
          yield point, *fields
        end
      rescue => e
        raise e, '%s:%d: %s' % [@path, index + 1, e]
      end
    end
    self
  end

  def each_with_unlisted
    previous = -1
    each do |point, *fields|
      (previous + 1).upto(point - 1) do |i|
        yield i, previous, true, *fields
      end
      yield point, point - 1, false, *fields
      previous = point
    end
    (previous + 1).upto(0x10ffff) do |i|
      yield i, previous, true
    end
    self
  end

private

  Code = 0

  def comment_or_empty?(line)
    line =~ /\A(?:#|\s*\Z)/
  end
end
