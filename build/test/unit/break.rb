# -*- coding: utf-8 -*-

class Break
  def initialize(path, method, io = $stdout)
    io.puts '# -*- coding: utf-8 -*-',
      '# Automatically generated, so don’t edit!',
      '',
      'Expectations do'
    Lines.new(path).each do |splits|
      io.printf "  expect [%s] do [%s].pack('U*').u.%s.to_a end\n",
        splits.map{ |e| "[%s].pack('U').u" % xify(e) }.join(', '),
        splits.map{ |s| xify(s) }.join(', '),
        method
    end
    io.puts 'end'
  end

private

  def xify(s)
    '0x%04x' % (s == 'D800' ? 0x0001 : s.to_i(16))
  end

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

Break.new ARGV[0], ARGV[1]
