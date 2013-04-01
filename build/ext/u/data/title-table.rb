# -*- coding: utf-8 -*-

require 'u/build'

class TitleTable
  def initialize(data, io = $stdout)
    U::Build::Header.new(io) do
      io.puts TitleTable.new(data)
    end
  end

private

  class TitleTable < U::Build::Header::Table
    def initialize(data)
      super "static const struct {
\tuint32_t ch;
\tuint32_t upper;
\tuint32_t lower;
} title_table[]"
      # TODO: Add #code to Entry and use #select on data here.
      data.each_with_index do |entry, code|
        next unless entry.title_to_lower
        self << U::Build::Header::Table::Row.new(*[code, entry.title_to_upper, entry.title_to_lower].map{ |i| '0x%04x' % i })
      end
    end
  end
end

TitleTable.new(Marshal.load(File.open(ARGV[0], 'rb', &:read)))
