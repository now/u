# -*- coding: utf-8 -*-

class Normalize
  def initialize(path, io = $stdout)
    @io = io
    @io.puts '# -*- coding: utf-8 -*-',
      '# Automatically generated, so don’t edit!',
      '',
      'Expectations do'
    Lines.new(path).each do |fields|
      generate fields[0..4].map{ |f| f.split(' ').map{ |i| i.to_i(16) }.pack('U*') }
    end
    @io.puts 'end'
  end

private

  def generate(cs)
    return if cs.any?{ |c| c.empty? }

    generate1 :nfc, cs[1], cs[0]
    generate1 :nfc, cs[1], cs[1]
    generate1 :nfc, cs[1], cs[2]

    generate1 :nfc, cs[3], cs[3]
    generate1 :nfc, cs[3], cs[4]

    generate1 :nfd, cs[2], cs[0]
    generate1 :nfd, cs[2], cs[1]
    generate1 :nfd, cs[2], cs[2]

    generate1 :nfd, cs[4], cs[3]
    generate1 :nfd, cs[4], cs[4]

    generate1 :nfkc, cs[3], cs[0]
    generate1 :nfkc, cs[3], cs[1]
    generate1 :nfkc, cs[3], cs[2]
    generate1 :nfkc, cs[3], cs[3]
    generate1 :nfkc, cs[3], cs[4]

    generate1 :nfkd, cs[4], cs[0]
    generate1 :nfkd, cs[4], cs[1]
    generate1 :nfkd, cs[4], cs[2]
    generate1 :nfkd, cs[4], cs[3]
    generate1 :nfkd, cs[4], cs[4]
  end

  def generate1(mode, expected, value)
    @io.printf "  expect '%s'.u do '%s'.u.normalize(%p) end\n",
      expected =~ /\A['\\]\Z/ ? "\\'" : expected,
      value =~ /\A['\\]\Z/ ? "\\'" : value,
      mode
  end

  class Lines
    include Enumerable

    def initialize(path)
      @path = path
    end

    def each
      File.open(@path, 'rb') do |file|
        file.enum_for(:each_line).with_index do |line, index|
          next if line =~ /\A(?:[@#]|\s*\Z)/
          fields = line.sub(/\s*;\s*#.*\Z/, '').split(/\s*;\s*/)
          raise RuntimeError,
            '%s:%d: wrong number of fields: %d instead of 5' %
              [@path, index + 1, fields.size] unless fields.size == 5
          yield fields
        end
      end
    end
  end

  Code, Status, Mapping = (0..2).to_a
end

Normalize.new ARGV[0]
