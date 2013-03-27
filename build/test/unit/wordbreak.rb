# -*- coding: utf-8 -*-

class WordBreak
  def initialize(path, io = $stdout)
    io.puts '# -*- coding: utf-8 -*-',
      '# Automatically generated, so don’t edit!',
      '',
      'Expectations do'
    Lines.new(path).each do |splits|
      io.printf "  expect [%s] do %s.u.words.to_a end\n",
        splits.map{ |e| '%s.u' % e.split(' ').map{ |s| s.hex }.pack('U*').dump }.join(', '),
        splits.join(' ').split(' ').map{ |s| s.hex }.pack('U*').dump
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
      File.open(@path, 'r') do |file|
        file.each_line.with_index do |line, index|
          next if line =~ /\A(?:#|\s*\Z)/
          yield line.gsub(/\s*\u{d7}\s*/, ' ').
            sub(/\A\s*\u{f7}\s*/, '').
            sub(/\s*#.*\Z/, '').
            split(/\s*\u{f7}\s*/)
        end
      end
    end
  end
end

WordBreak.new ARGV[0]
