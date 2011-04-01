# -*- coding: utf-8 -*-

class FoldCase
  def initialize(path, io = $stdout)
    io.puts '# -*- coding: utf-8 -*-',
      '# Automatically generated, so don’t edit!',
      '',
      'Expectations do'
    Lines.new(path).each do |fields|
      io.printf "  expect '%s'.u do '%s'.u.foldcase end\n",
        fields[Mapping].split(' ').map{ |s| s.hex }.pack('U*'),
        [fields[Code].hex].pack('U')
    end
    io.puts 'end'
  end

private

  class Lines
    include Enumerable

    def initialize(path)
      @path = path
    end

    def each
      File.open(@path, 'rb') do |file|
        file.each_line.with_index do |line, index|
          next if line =~ /\A(?:#|\s*\Z)/
          fields = line.sub(/\s*;\s*#.*\Z/, '').split(/\s*;\s*/)
          raise RuntimeError,
            '%s:%d: wrong number of fields: %d instead of 3' %
              [@path, index + 1, fields.size] unless fields.size == 3
          next if fields[Status] == 'S' or fields[Status] == 'T'
          yield fields
        end
      end
    end
  end

  Code, Status, Mapping = (0..2).to_a
end

FoldCase.new ARGV[0]
